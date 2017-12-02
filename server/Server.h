//
// Created by liora on 02/12/17.
//

#ifndef OTHELLO_SERVER_H
#define OTHELLO_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

class Server {
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int something);
    int calc(int arg1, const char op, int arg2) const;

public:
    Server(int port);
    void start();
    void stop();
};


#endif //OTHELLO_SERVER_H
