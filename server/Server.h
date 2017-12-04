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
    int handleClient(int srcSocket, int dstSocket);
    int readMove(int readSocket, int* buffer, size_t sizeBuffer);
    int writeMove(int writeSocket, int* buffer, size_t sizeBuffer);
    int transferMessage(int readSocket, int writeSocket, int * buffer);
    void initializingPlayer(int playerSocket, int playerNum);

public:
    Server(int port);
    void start();
    void stop();
};


#endif //OTHELLO_SERVER_H
