#include <cstdlib>
#include <strings.h>
#include "Server.h"
#define END_GAME -2
#define FREE_ROOM -5
#define IN_PROGRESS 0

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0), commandsManager(this) {}
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
  struct sockaddr_in playerAddress1;
  struct sockaddr_in playerAddress2;
  socklen_t playerAddressLen1 = sizeof((struct sockaddr *) &playerAddress1);
  socklen_t playerAddressLen2 = sizeof((struct sockaddr *) &playerAddress2);


  /*while (true) {
    cout << "Waiting for player X to connect..." << endl;
    // Accept a new client connection
    int playerSocket1 = accept(serverSocket, (struct sockaddr *) &playerAddress1, &playerAddressLen1);
    if (playerSocket1 == -1) throw "Error on accept";
    //Player* player1 = new RemotePlayer(Tile(X), playerSocket1);
    cout << "Player X connected. Waiting for player O to connect..." << endl;
    // Accept a new client connection
    int playerSocket2 = accept(serverSocket, (struct sockaddr *) &playerAddress2, &playerAddressLen2);
    if (playerSocket2 == -1) throw "Error on accept";
    cout << "Player O connected." << endl;

    initializingPlayer(playerSocket1, 0);
    initializingPlayer(playerSocket2, 1);

    int gameStatus = IN_PROGRESS;
    while (gameStatus != END_GAME) {
      gameStatus = transferMessage(playerSocket1, playerSocket2);
      if (gameStatus == END_GAME) break;
      gameStatus = transferMessage(playerSocket2, playerSocket1);
    }
    close(playerSocket1);
    close(playerSocket2);
  }*/
  close(serverSocket);

}

/*void Server::initializingPlayer(int playerSocket, int playerNum) {
  ssize_t x = write(playerSocket, &playerNum, sizeof(playerNum));
  if (x == -1) {
    cout << "Error writing to socket" << endl;
    exit(1);
  }
}*/

// Handle requests from a specific client
int Server::handleClient(int clientSocket) {
  string command, arg;
  vector<string> args;
  ssize_t r = read(clientSocket, &command, sizeof(command));
  if (r == -1) {
    cout << "Error reading command from player." << endl;
    return END_GAME;
  }
  if (r == 0) {
    cout << "player disconnected" << endl;
    return END_GAME;
  }
  while (read(clientSocket, &arg, sizeof(arg)) > 0) {
    args.push_back(arg);
  }
  commandsManager.executeCommand(command, args);

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
  for (int i = 0; i < gamesList.size(); ++i) {
    if (gamesList[i].isStarted()) continue;
    ssize_t w = write(clientSocket, &gamesList[i].getName(), sizeof(gamesList[i].getName()));
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
  int result = inGamesList(gameName ,clientSocket);
  if (result == FREE_ROOM) gamesList.push_back(GameRoom(clientSocket, gameName));
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
  for (int i = 0; i < gamesList.size(); ++i) {
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
