//
// Created by liora on 02/12/17.
//

#include <cstdlib>
#include "Server.h"
#define END_GAME -1
#define IN_PROGRESS 0

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0) {}

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
  socklen_t playerAddressLen1;
  socklen_t playerAddressLen2;
  while (true) {
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
      gameStatus = handleClient(playerSocket2, playerSocket1);
      if (gameStatus == END_GAME) break;
      gameStatus = handleClient(playerSocket1, playerSocket2);
    }
    close(playerSocket1);
    close(playerSocket2);
  }
}

void Server::initializingPlayer(int playerSocket, int playerNum) {
  ssize_t x = write(playerSocket, &playerNum, sizeof(playerNum));
  if (x == -1) {
    cout << "Error writing to socket" << endl;
    exit(1);
  }
}

// Handle requests from a specific client
int Server::handleClient(int readSocket, int writeSocket) {
    int moveVal;
  //gets x and y value of move and transfer it from onr player to the other.
    moveVal = transferMessage(readSocket, writeSocket, moveVal);
    if (moveVal == END_GAME) return END_GAME;
    return transferMessage(readSocket, writeSocket, moveVal);
}

int Server::transferMessage(int readSocket, int writeSocket, int buffer) {
    int result = readMove(readSocket, buffer, sizeof(buffer));
    return writeMove(writeSocket, result, sizeof(buffer));
}

int Server::readMove(int readSocket, int buffer, size_t sizeBuffer) {
  ssize_t r = read(readSocket, &buffer, sizeof(buffer));
  if (r == -1) {
    cout << "Error reading move from player." << endl;
    exit(1);
  }
  if (r == 0) {
    cout << "Player disconnected" << endl;
    exit(1);
  }
  //if (buffer[0] == END_GAME) return END_GAME;
  return buffer;
}

int Server::writeMove(int writeSocket, int buffer, size_t sizeBuffer) {
  ssize_t w = write(writeSocket, &buffer, sizeBuffer);
  if (w == -1) {
    cout << "Error getting move from player." << endl;
    exit(1);
  }
  if (w == 0) {
    cout << "Player disconnected" << endl;
    exit(1);
  }
  //if (buffer[0] == END_GAME) return END_GAME;
  return (int)w;
}

void Server::stop() {
  close(serverSocket);
}
