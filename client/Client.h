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

class Client {
public:
  Client(const char *serverIP, int serverPort);
  void connectToServer();
  //string sendMove();
  int getClientSocket() const;
 private:
  const char *serverIP;
  int serverPort;
  int clientSocket;
};

#endif //OTHELLO_CLIENT_H
