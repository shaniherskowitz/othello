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
  Client(const char *serverIP, int serverPort);
  void connectToServer();
  int sendExercise(int arg1, char op, int arg2);
 private:
  const char *serverIP;
  int serverPort;
  int clientSocket;
};

#endif //OTHELLO_CLIENT_H
