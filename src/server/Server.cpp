#include <cstdlib>
#include <strings.h>
#include "Server.h"
#define END_GAME -2
#define FREE_ROOM -5
#define IN_PROGRESS 0
#include "commands/CommandsManager.h"
#include <sstream>
#include <iterator>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0), gamesList() {}
void Server::connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen) {
  while (true) {
    cout << "Waiting for  client connections..." << endl;
    // Accept a new client connection
    int clientSocket = accept(serverSocket, (struct sockaddr *) &playerAddress1, &playerAddressLen);
    if (clientSocket == -1) throw "Error on accept";
    cout << "Client connected" << endl;
    handleClient(clientSocket);

    close(clientSocket);

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

// Handle requests from a specific client
int Server::handleClient(int clientSocket) {
  string command, arg;
  vector<string> args;
  CommandsManager commandsManager(this);
  while (true) {
    ssize_t r = read(clientSocket, &command, sizeof(command));
    if (r == -1) {
      cout << "Error reading command from player." << endl;
      return END_GAME;
    }
    if (r == 0) {
      cout << "player disconnected" << endl;
      return END_GAME;
    }
    istringstream iss(command);
    copy(istream_iterator<std::string>(iss), istream_iterator<string>(), back_inserter(args));
    commandsManager.executeCommand(args[0], args);
  }

  return 1;
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
  int size = gamesList.size();
  ssize_t w;
  for (int i = -1; i < size; ++i) {
    if (i == -1) w = write(clientSocket, &size, sizeof(int));
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
int Server::newGame(string &gameName, int clientSocket) {
  int result = inGamesList(gameName, clientSocket);
  if (result == FREE_ROOM) {
    GameRoom *room = new GameRoom(clientSocket, gameName);
    gamesList.push_back(*room);
  }
  return result;
}
int Server::joinGame(string &gameName, int clientSocket) {
  int result = inGamesList(gameName, clientSocket);
  if (result != FREE_ROOM && result != END_GAME) {
    gamesList[result].connectPlayer2(clientSocket);
    gamesList[result].startGame();
  }
  return result;
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
      return i;
    }
  }
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
