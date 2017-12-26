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
  int serverSocket; // the socket's file descriptor
  static bool stopServer;

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
   * The method closes the socket.
   */
  void handleClient(int clientSocket);
  /**
   * The method reads the move from the client.
   * @param readSocket The client's socket number.
   * @param buffer The buffer to which the move will be read to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or end game value.
   */
  static void *handleClientHelper(void *tempArgs);
  static void exitCondition();
  bool exitConnectionThreads();
  void stop();
  void connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen);
  string readString(int clientSocket);
  int readError(int numCheck);
};

#endif //OTHELLO_SERVER_H
