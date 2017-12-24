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


/**
 * Defining a Server class to transfer information between the Client's.
 */
class Server {
  int port;
  int serverSocket; // the socket's file descriptor
  vector<GameRoom> gamesList;
  /**
   * The method handles the client, by calling a function to transfer
   * messages between two client's.
   * @param srcSocket The socket of the client sending the message.
   * @return A value to determine the running of the message loop.
   */
  int handleClient(int clientSocket);
  /**
   * The method reads the move from the client.
   * @param readSocket The client's socket number.
   * @param buffer The buffer to which the move will be read to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or end game value.
   */
  Point readMove(int readSocket, Point buffer);
  /**
   * The method writes the move to the clients.
   * @param writeSocket The client's socket number.
   * @param buffer The buffer which the move will be written to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or the end game value.
   */
  int writeMove(int writeSocket, Point buffer, size_t sizeBuffer);
  /**
   * The method transfer's the move from the readSocket client to the
   * writeSocket client.
   * @param readSocket The client's of which we're reading from socket
   * @param writeSocket The client's of which we're writing to socket.
   * @param buffer The message being transferred.
   * @return The message value or a value to stp communication.
   */
  int transferMessage(int readSocket, int writeSocket, Point moveVal);

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
  void stop();
    string readString(int clientSocket);
  void connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen);
  int sendGamesList(int clientSocket);
  int newGame(string &gameName, int clientSocket);
  int joinGame(string &gameName, int clientSocket);
  int inGamesList(string &gameName, int clientSocket);
  void closeGame(string &gameName);
  void playMove(string &gameName, int clientSocket, Point move);
};

#endif //OTHELLO_SERVER_H
