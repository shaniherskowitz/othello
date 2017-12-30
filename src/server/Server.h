//
// Created by liora on 02/12/17.
//

#ifndef OTHELLO_SERVER_H
#define OTHELLO_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include <vector>
#include "Point.h"
#include "GameRoom.h"
#include "ServerGames.h"

/**
 * Defining a Server class to transfer information between the Client's.
 */
class Server {
 private:
  int port;
  static int serverSocket;
  static bool stopServer;

  /**
   * The method is a static helper function for HandleClient.
   * @param tempArgs HandleClient's arguments.
   * @return void* so can be sent to pthread_t create.
   */
  static void *handleClientHelper(void *tempArgs);

  /**
  * The method is a static helper function to listen for commands to shut the
  * server.
  * @param args The method gets no args-there for convention.
  * @return void* so can be sent to pthread_t create.
  */
  static void *waitForExit(void *args);

 public:

  /**
   * The Server's constructor.
   * @param port The server's port number.
   */
  explicit Server(int port);

  /**
   * The method opens a socket, and waits for connections.
   */
  void start();

  /**
   * The method takes care of the client's request.
   * @param clientSocket The client socket.
   */
  void handleClient(int clientSocket);

  /**
   * The method stops the incoming connections, disconnects the existing
   * connections from the server socket, and disconnecting the server.
   */
  void stop();

  /**
   * The method listens for client connection and accepts them.
   * @param playerAddress The player address.
   * @param playerAddressLen The length of the player address.
   */
  void connectToClient(sockaddr_in playerAddress, socklen_t playerAddressLen);

  /**
   * The method reads a string from the socket.
   * @param clientSocket The client ocket.
   * @return The sent string.
   */
  string readString(int clientSocket);

  /**
   * The method checks if an error was made while read/write from socket.
   * @param numCheck The read/write method return parameter.
   * @return The check/mistake.
   */
  ssize_t readError(ssize_t numCheck);

  /**
   * The method closes all threads from the pthread vector.
   * @param threads The pthread_t vector.
   */
  void closeThreads(vector<pthread_t> threads);
};

#endif //OTHELLO_SERVER_H
