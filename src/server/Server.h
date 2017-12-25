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

 protected:
  int port;
  int serverSocket; // the socket's file descriptor
  /**
   * The method writes the move to the clients.
   * @param writeSocket The client's socket number.
   * @param buffer The buffer which the move will be written to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or the end game value.
   */
  int writeMove(int writeSocket, Point buffer, size_t sizeBuffer);

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
  int handleClient(int clientSocket);
  /**
   * The method reads the move from the client.
   * @param readSocket The client's socket number.
   * @param buffer The buffer to which the move will be read to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or end game value.
   */
  static void *handleClientHelper(void *tempArgs);
  void stop();
    //string readString(int clientSocket);
  void connectToClient(struct sockaddr_in playerAddress1, socklen_t playerAddressLen);
  int sendGamesList(int clientSocket);
  int newGame(string &gameName, int clientSocket);
  int joinGame(string &gameName, int clientSocket);
  int inGamesList(string &gameName, int clientSocket);
  void closeGame(string &gameName);
  void playMove(int clientSocket, Point move);
  int getAvialbleGames();
  string readString(int clientSocket);
    void writeInt(int clientSocket, int num);
    vector<GameRoom>::iterator getGame(string gameName);
};
//ServerGames Server::gamesList = ServerGames();

#endif //OTHELLO_SERVER_H
