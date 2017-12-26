#include <cstdlib>
#include <strings.h>
#include "Server.h"
#define END_GAME -2
#include "commands/CommandsManager.h"
#include "ServerGames.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define CLOSE_GAME ""

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0) {}

bool Server::stopServer = false;

void Server::connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen) {
  vector<pthread_t> connectionThreads;
  stopServer = false;
  while (!stopServer) {
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
    //pthread_exit(exitCondition());
  }
  stop();
  pthread_exit(NULL);
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
void Server::handleClient(int clientSocket) {
  //int s = gamesList.size();
  stringstream ss;
  ss << clientSocket;
  string socketString = ss.str();
  ServerGames *gamesList = ServerGames::Instance();
  CommandsManager commandsManager(gamesList);
  while (true) {
    string command, arg;
    vector<string> args;
    args.push_back(socketString);
    command = readString(clientSocket);
    if (command.empty()) return;
    istringstream iss(command);
    copy(istream_iterator<std::string>(iss), istream_iterator<string>(), back_inserter(args));
    commandsManager.executeCommand(args[1], args);
  }
}

string Server::readString(int clientSocket) {
  int commandSize;
  char buffer[50];
  ssize_t r = read(clientSocket, &commandSize, sizeof(int));
  if (readError((int) r) != 1) return CLOSE_GAME;

  for (int i = 0; i < commandSize; i++) {
    r = read(clientSocket, &buffer[i], sizeof(char));
    int k = readError((int) r);
    if (k != 1) return CLOSE_GAME;
  }
  buffer[commandSize] = '\0';
  return string(buffer);
}

int Server::readError(int numCheck) {
  if (numCheck == -1) {
    cout << "Error reading command from player." << endl;
    return numCheck;
  }
  if (numCheck == 0) {
    cout << "player disconnected" << endl;
    return numCheck;
  }
  return 1;
}

void Server::exitCondition() {
  stopServer = true;
}

bool Server::exitConnectionThreads() {
  return false;
}

void Server::stop() {
  close(serverSocket);
}
