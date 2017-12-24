#include <cstdlib>
#include <strings.h>
#include "Server.h"
#define END_GAME -2
#define FREE_ROOM -5
#define IN_PROGRESS 0
#include "commands/CommandsManager.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <cmath>
pthread_mutex_t count_mutex;
#define THREADS_NUM 10
vector<GameRoom> gamesList;
using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0) {}
void Server::connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen) {
  pthread_t connectionThreads[THREADS_NUM];
  //int clientSockets[THREADS_NUM];
  for (int i = 0; i < THREADS_NUM; i++) {
    cout << "Waiting for  client connections..." << endl;
    // Accept a new client connection
    int clientSocket = accept(serverSocket, (struct sockaddr *) &playerAddress1, &playerAddressLen);
    if (clientSocket == -1) throw "Error on accept";
    cout << "Client connected" << endl;
    int rc = pthread_create(&connectionThreads[i], NULL, &Server::handleClientHelper, &clientSocket);
    if (rc != 0) {
      cout << "Error: unable to create thread, " << rc << endl;
      exit(-1);
    }
    //handleClient(clientSocket);

    //close(clientSocket);
  }
  /*while (true) {
    cout << "Waiting for  client connections..." << endl;
    // Accept a new client connection
    int clientSocket = accept(serverSocket, (struct sockaddr *) &playerAddress1, &playerAddressLen);
    if (clientSocket == -1) throw "Error on accept";
    cout << "Client connected" << endl;
    handleClient(clientSocket);

    close(clientSocket);

  }*/
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
  int clientSocket =  *((int *)tempArgs);
  ((Server *)tempArgs)->handleClient(clientSocket);
  return tempArgs;
}

// Handle requests from a specific client
int Server::handleClient(int clientSocket) {
  //int clientSocket = *((int *)args);
  pthread_mutex_lock(&count_mutex);
  int s = gamesList.size();
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
    //ssize_t r = read(clientSocket, &command, sizeof(command));
    /*if (r == -1) {
      cout << "Error reading command from player." << endl;
      //return (void*)END_GAME;
    }
    if (r == 0) {
      cout << "player disconnected" << endl;
      return (void*)END_GAME;
    }*/
    istringstream iss(command);
    copy(istream_iterator<std::string>(iss), istream_iterator<string>(), back_inserter(args));
    commandsManager.executeCommand(args[1], args);
    pthread_mutex_unlock(&count_mutex);
  }

  //return 1;
}


int Server::transferMessage(int readSocket, int writeSocket, Point moveVal) {
  Point result = readMove(readSocket, moveVal);
  int result2 = writeMove(writeSocket, result, sizeof(result));
  if (result.getX() == END_GAME && result2 == END_GAME) return END_GAME;
  return result2;
}

Point Server::readMove(int readSocket, Point buffer) {
  if (buffer.getX() == END_GAME) return Point(END_GAME, END_GAME);
  ssize_t r = read(readSocket, &buffer, sizeof(buffer));
  if (r == -1) {
    cout << "Error reading move from player." << endl;
    return Point(END_GAME, END_GAME);
  }
  if (r == 0) {
    cout << "Both players disconnected" << endl;
    return Point(END_GAME, END_GAME);
  }
  return buffer;
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
  int listSize = getAvialbleGames();
  ssize_t w;
  int s = gamesList.size();
  for (int i = -1; i < s; ++i) {
    if (i == -1) w = write(clientSocket, &listSize, sizeof(int));
    else {
      if (gamesList[i].isStarted()) continue;
      w = write(clientSocket, &gamesList[i].getName(), sizeof(gamesList[i].getName()));
    }
    if (w == -1) {
      cout << "Error writing gamesList to player" << endl;
      return END_GAME;
    }
    if (w == 0) {
      cout << "Player disconnected" << endl;
      return END_GAME;
    }
  }
}
int Server::getAvialbleGames() {
  int count = 0;
  pthread_mutex_lock(&count_mutex);
  for (int i = 0; i < gamesList.size(); ++i) {
    if (!gamesList[i].isStarted()) count++;
  }
  pthread_mutex_unlock(&count_mutex);
  return count;
}
int Server::newGame(string &gameName, int clientSocket) {
  int result = inGamesList(gameName, clientSocket);
  if (result == FREE_ROOM) {
    GameRoom *room = new GameRoom(clientSocket, gameName);
    pthread_mutex_lock(&count_mutex);
    gamesList.push_back(*room);
    pthread_mutex_unlock(&count_mutex);
  }
  return result;
}
int Server::joinGame(string &gameName, int clientSocket) {
  int result = inGamesList(gameName, clientSocket);
  if (result != FREE_ROOM && result != END_GAME) {
    pthread_mutex_lock(&count_mutex);
    gamesList[result].connectPlayer2(clientSocket);
    gamesList[result].startGame();
    pthread_mutex_unlock(&count_mutex);
  }
  return result;
}

int Server::inGamesList(string &gameName, int clientSocket) {
  int problem = -1;
  pthread_mutex_lock(&count_mutex);
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
      return (int)i;
    }
  }
  pthread_mutex_unlock(&count_mutex);
  return FREE_ROOM;
}
void Server::playMove(string &gameName, int clientSocket, Point move) {
  int gameToPlay = inGamesList(gameName, clientSocket);
  if (gameToPlay != FREE_ROOM && gameToPlay != END_GAME)
    transferMessage(clientSocket, gamesList[gameToPlay].getOtherSocket(clientSocket), move);
}

void Server::closeGame(string &gameName) {
  for (int i = 0; i < gamesList.size(); ++i) {
    if (gamesList[i].getName() == gameName) {
      gamesList[i].closeGame();
      return;
    }
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