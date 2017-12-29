//
// Created by shani herskowitz on 12/2/17.
//

#ifndef OTHELLO_CLIENT_H
#define OTHELLO_CLIENT_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "../server/Server.h"

using namespace std;

/**
 * Defining a Client class to exchange information with the server.
 */
class Client {
  const char *serverIP;
  int serverPort;
  int clientSocket;
 public:
  /**
   * The Client's constructor.
   * @param serverIP The Server's IP address.
   * @param serverPort The Server's port number.
   */
  Client(const char *serverIP, int serverPort);
  /**
   * The method opens a socket from the Client's side to establish a
   * communication with the server.
   */
  void connectToServer();
  /**
   * The method returns the Client's socket number.
   * @return The Client's socket number.
   */
  int getClientSocket() const;
};

#endif //OTHELLO_CLIENT_H
