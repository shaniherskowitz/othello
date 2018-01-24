#include <cstdlib>
#include "Server.h"
#define END_GAME -2
#include "commands/CommandsManager.h"
#include "Task.h"
#include "ThreadPool.h"
#include <sstream>
#include <iterator>
#include <cmath>
#include <cstring>
#define CLOSE_GAME ""

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

Server::Server(int port) : port(port) {}

bool Server::stopServer = false;

int Server::serverSocket = 0;
ThreadPool pool(5);

void Server::connectToClient(sockaddr_in playerAddress, socklen_t playerAddressLen) {
  //ThreadPool pool = ThreadPool(2);
  int i = 1;
  Task *task1 = new Task(waitForExit, (void *)i);
  pool.addTask(task1);

  while (!stopServer) {
    cout << "Waiting for  client connections..." << endl;
    int clientSocket = accept(serverSocket, (struct sockaddr *) &playerAddress, &playerAddressLen);
    if (clientSocket == -1) {
      cout << "Server Disconnecting" << endl;

      pthread_exit(NULL);
    }

    cout << "Client connected" << endl;
    Task *task = new Task(handleClientHelper, (void *)clientSocket);
    pool.addTask(task);



  }
}

void *Server::waitForExit(void *args) {
  ((Server *) args)->stop();
  return args;
}


void Server::start() {
  // Create a socket point
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) throw "Error opening socket";
  int enable = 1;
  if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) throw("setsockopt(SO_REUSEADDR) failed");

  // Assign a local address to the socket
  struct sockaddr_in serverAddress;
  bzero((void *) &serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);
  if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
    throw "Error on binding";

  // Start listening to incoming connections
  listen(serverSocket, MAX_CONNECTED_CLIENTS);

  // Define the client socket's structures
  struct sockaddr_in playerAddress;
  socklen_t playerAddressLen = sizeof((struct sockaddr *) &playerAddress);

  connectToClient(playerAddress, playerAddressLen);
}

void *Server::handleClientHelper(void *tempArgs) {
  long clientSocket = (long)tempArgs;
  ((Server *) tempArgs)->handleClient((int)clientSocket);
  return tempArgs;
}

// Handle requests from a specific client
void Server::handleClient(int clientSocket) {
  stringstream ss;
  ss << clientSocket;
  string socketString = ss.str();
  ServerGames *gamesList = ServerGames::Instance();
  CommandsManager commandsManager(gamesList);
  //while (true) {
    string command, arg;
    vector<string> args;
    args.push_back(socketString);
    command = readString(clientSocket);
    if (command.empty()) return;
    istringstream iss(command);
    copy(istream_iterator<std::string>(iss), istream_iterator<string>(), back_inserter(args));
    commandsManager.executeCommand(args[1], args);
    pool.addTask(new Task(handleClientHelper, (void *)clientSocket));
    //sleep(1);
  //}
}

string Server::readString(int clientSocket) {
  int commandSize;
  char buffer[50];
  ssize_t r = read(clientSocket, &commandSize, sizeof(int));
  if (readError(r) != 1) return CLOSE_GAME;
  for (int i = 0; i < commandSize; i++) {
    r = read(clientSocket, &buffer[i], sizeof(char));
    ssize_t k = readError(r);
    if (k != 1) return CLOSE_GAME;
  }
  buffer[commandSize] = '\0';
  return string(buffer);
}

ssize_t Server::readError(ssize_t numCheck) {
  if (serverSocket == 0) return 0;
  if (numCheck == -1) return numCheck;
  if (numCheck == 0) {
    cout << "player disconnected" << endl;
    return numCheck;
  }
  return 1;
}

void Server::stop() {
  string exitServer;
  while (exitServer != "exit") {
    cout << "To disconnect the server at any stage please enter exit:" << endl << endl;

    cin >> exitServer;
  }
  stopServer = true;
  vector<string> args;
  ServerGames *gamesList = ServerGames::Instance();
  CommandsManager commandsManager(gamesList);
  commandsManager.executeCommand("exit", args);
  ServerGames::lastCall = true;
  ServerGames::deleteInstance();
  shutdown(serverSocket, SHUT_RDWR);
  close(serverSocket);
  pool.terminate();
}
