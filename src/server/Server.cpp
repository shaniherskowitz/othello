#include <cstdlib>
#include <strings.h>
#include "Server.h"
#define END_GAME -2
#define FREE_ROOM -5
#define IN_PROGRESS 0
#include "commands/CommandsManager.h"
#include "ServerGames.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <cmath>
#include <cstring>

pthread_mutex_t count_mutex;
vector<GameRoom> gamesList;
//ServerGames gamesList = ServerGames();
using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0) {}
void Server::connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen) {
  //pthread_t connectionThreads[THREADS_NUM];
  vector<pthread_t> connectionThreads;
  //int clientSockets[THREADS_NUM];
  while(true) {
    cout << "Waiting for  client connections..." << endl;
    // Accept a new client connection
    int clientSocket = accept(serverSocket, (struct sockaddr *) &playerAddress1, &playerAddressLen);
    if (clientSocket == -1) throw "Error on accept";
    cout << "Client connected" << endl;
    pthread_t currThread;
    int rc = pthread_create(&currThread, NULL, &Server::handleClientHelper, &clientSocket);
    if (rc != 0) {
      cout << "Error: unable to create thread, " << rc << endl;
      exit(-1);
    }
    connectionThreads.push_back(currThread);

    //close(clientSocket);
  }
}
void Server::start() {

  // Create a socket point
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) throw "Error opening socket";

  // Assign a local address to the socket
  struct sockaddr_in serverAddress;
  bzero((void *) &serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);
  if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
    throw "Error on binding";
  }

  // Start listening to incoming connections
  listen(serverSocket, MAX_CONNECTED_CLIENTS);
  // Define the client socket's structures
  struct sockaddr_in playerAddress;
  socklen_t playerAddressLen = sizeof((struct sockaddr *) &playerAddress);

  connectToClient(playerAddress, playerAddressLen);
  close(serverSocket);

}

void *Server::handleClientHelper(void *tempArgs) {
  int clientSocket = *((int *) tempArgs);
  ((Server *) tempArgs)->handleClient(clientSocket);
  return tempArgs;
}

// Handle requests from a specific client
int Server::handleClient(int clientSocket) {
  //int s = gamesList.size();
  stringstream ss;
  ss << clientSocket;
  string socketString = ss.str();
  CommandsManager commandsManager(this);
  while (true) {
    string command, arg;
    vector<string> args;
    args.push_back(socketString);
    command = readString(clientSocket);
    if (command.empty()) return END_GAME;
    istringstream iss(command);
    copy(istream_iterator<std::string>(iss), istream_iterator<string>(), back_inserter(args));
    commandsManager.executeCommand(args[1], args);
  }

  //return 1;
}


int Server::writeMove(int writeSocket, Point buffer, size_t sizeBuffer) {
  if (buffer.getX() == END_GAME) return END_GAME;
  ssize_t w = write(writeSocket, &buffer, sizeBuffer);
  if (w == -1) {
    cout << "Error getting move from player." << endl;
    return END_GAME;
  }
  if (w == 0) {
    cout << "Both Players disconnected" << endl;
    return END_GAME;
  }
  return (int) w;
}
int Server::sendGamesList(int clientSocket) {
  int numWords = getAvialbleGames();
  writeInt(clientSocket, numWords);
  vector<GameRoom>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if (it->isStarted()) continue;
    string game = it->getName();
    unsigned long gameSize = game.size();
    writeInt(clientSocket, gameSize);
    for (int i = 0; i < gameSize; i++) {
      char send = game[i];
      ssize_t w = write(clientSocket, &send, sizeof(char));
      if (w == -1) {
        cout << "Error writing gamesList to player" << endl;
        return END_GAME;
      }
      if (w == 0) {
        cout << "Player disconnected" << endl;
        return END_GAME;
      }
    }
    it++;
  }
}

vector<GameRoom>::iterator Server::getGame(string gameName) {
  vector<GameRoom>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if (it->getName() == gameName) return it;
    it++;
  }
  return it;
}

int Server::getAvialbleGames() {
  int count = 0;
  //pthread_mutex_lock(&count_mutex);
  for (int i = 0; i < gamesList.size(); ++i) {
    if (!gamesList[i].isStarted()) count++;
  }
 // pthread_mutex_unlock(&count_mutex);
  return count;
}
int Server::newGame(string &gameName, int clientSocket) {
  if (getGame(gameName) != gamesList.end()) {
    int gameExists = -1;
    write(clientSocket, &gameExists, sizeof(gameExists));
  }
  GameRoom *gameRoom = new GameRoom(clientSocket, gameName);
  pthread_mutex_trylock(&count_mutex);
  gamesList.push_back(*gameRoom);
  pthread_mutex_unlock(&count_mutex);
}

int Server::joinGame(string &gameName, int clientSocket) {
  vector<GameRoom>::iterator gameRoom = getGame(gameName);
  if (gameRoom != gamesList.end() && !gameRoom->isStarted()) {
    pthread_mutex_trylock(&count_mutex);
    gameRoom->connectPlayer2(clientSocket);
    gameRoom->startGame();
    pthread_mutex_unlock(&count_mutex);
  }
}

int Server::inGamesList(string &gameName, int clientSocket) {
  int problem = -1;
  unsigned long size = gamesList.size();
  for (unsigned long i = 0; i < size; i++) { //not working why??
    if (gamesList[i].getName() == gameName) {
      ssize_t w = write(clientSocket, &problem, sizeof(int));
      if (w == -1) {
        cout << "Error writing gamesList to player" << endl;
        return END_GAME;
      }
      if (w == 0) {
        cout << "Player disconnected" << endl;
        return END_GAME;
      }
      return (int) i;
    }
  }
  return FREE_ROOM;
}
void Server::playMove(int clientSocket, Point move) {
  for(int i = 0; i< gamesList.size(); i++) {
    if(gamesList[i].playingInGame(clientSocket)) {
      GameRoom *gameRoom = &gamesList[i];
      writeMove(gameRoom->getOtherSocket(clientSocket), move, sizeof(move));
      break;
    }
  }
}

void Server::closeGame(string &gameName) {
  vector<GameRoom>::iterator gameRoom = getGame(gameName);
  if (gameRoom != gamesList.end()) {
    gameRoom->closeGame();
    gamesList.erase(gameRoom);
  }
}

void Server::stop() {
  close(serverSocket);
}

string Server::readString(int clientSocket) {
  int commandSize;
  char buffer[50];
  ssize_t r = read(clientSocket, &commandSize, sizeof(int));
  if (r == -1) {
    cout << "Error reading command from player." << endl;
    return "";
  }
  if (r == 0) {
    cout << "player disconnected" << endl;
    return "";
  }
  for (int i = 0; i < commandSize; i++) {
    r = read(clientSocket, &buffer[i], sizeof(char));
    if (r == -1) {
      cout << "Error reading command from player." << endl;
      return "";
    }
    if (r == 0) {
      cout << "player disconnected" << endl;
      return "";
    }
  }
  buffer[commandSize] = '\0';
  return string(buffer);
}

void Server::writeInt(int clientSocket, int num) {
  ssize_t w = write(clientSocket, &num, sizeof(num));
  if (w == -1) {
    cout << "Error writing gamesList to player" << endl;
    return;
  }
  if (w == 0) {
    cout << "Player disconnected" << endl;
    return;
  }
}