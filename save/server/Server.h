//
// Created by liora on 02/12/17.
//

#ifndef OTHELLO_SERVER_H
#define OTHELLO_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

/**
 * Defining a Server class to transfer information between the Client's.
 */
class Server {
  int port;
  int serverSocket; // the socket's file descriptor
  /**
   * The method handles the client, by calling a function to transfer
   * messages between two client's.
   * @param srcSocket The socket of the client sending the message.
   * @param dstSocket The socket of the client receiving the message.
   * @return A value to determine the running of the message loop.
   */
  int handleClient(int srcSocket, int dstSocket);
  /**
   * The method reads the move from the client.
   * @param readSocket The client's socket number.
   * @param buffer The buffer to which the move will be read to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or end game value.
   */
  int readMove(int readSocket, int buffer);
  /**
   * The method writes the move to the clients.
   * @param writeSocket The client's socket number.
   * @param buffer The buffer which the move will be written to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or the end game value.
   */
  int writeMove(int writeSocket, int buffer, size_t sizeBuffer);
  /**
   * The method transfer's the move from the readSocket client to the
   * writeSocket client.
   * @param readSocket The client's of which we're reading from socket
   * @param writeSocket The client's of which we're writing to socket.
   * @param buffer The message being transferred.
   * @return The message value or a value to stp communication.
   */
  int transferMessage(int readSocket, int writeSocket, int buffer);
  /**
   * The method initializes the player who is a client.
   * @param playerSocket The player's socket number.
   * @param playerNum A number to represent the symbol of the player.
   */
  void initializingPlayer(int playerSocket, int playerNum);

 public:
  /**
   * The Server's constructor.
   * @param port The server's port number.
   */
  Server(int port);
  /**
   * The method opens a socket, and waits for connections.
   */
  void start();
  /**
   * The method closes the socket.
   */
  void stop();
};

#endif //OTHELLO_SERVER_H
