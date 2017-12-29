#ifndef OTHELLO_OTHELLO_SERVERGAMES_H
#define OTHELLO_OTHELLO_SERVERGAMES_H

#include <vector>
#include "GameRoom.h"

/**
 * Defining a singleton ServerGames class to transfer the communication between
 * the client's and server regarding the played game.
 */
class ServerGames {
  static ServerGames *instance;
  vector<GameRoom> gamesList;

    /**
     * The ServerGames constructor.
     */
  ServerGames() {};

    /**
     * The ServerGame destructor.
     */

    ~ServerGames();

    /**
     * The ServerGames constructor.
     * @param serverGames1 The instance.
     */
  ServerGames(ServerGames &serverGames1) {};

    /**
     * The method blocks the = operator, singleton convention.
     * @return ServerGames instance.
     */
  ServerGames &operator=(ServerGames const &);

    /**
     * The method returns an iterator to a game belonging to the gameList
     * with the given name.
     * @param gameName The gameRoom's name.
     * @return An iterator to it's location on the gamesList.
     */
    vector<GameRoom>::iterator getGame(string gameName);

 public:
    /**
     * The ServerGames static constructor, in order to implement a singleton
     * object.
     * @return The ServerGames instance.
     */
  static ServerGames *Instance();

    /**
     * The ServerGames static destructor, in order to implement a singleton
     * object.
     */
  static void deleteInstance();

    /**
     * The method closes all games from the gamesList;
     */
  void closeGames();

    /**
     * The method creates a new game to be added to game list of name gameName.
     * @param gameName The gameRoom's name.
     * @param clientSocket The client socket creating the game.
     */
  void newGame(string gameName, int clientSocket);

    /**
     * The method joins client of clientSocket to game of gameName on the list.
     * @param gameName The gameRoom's name.
     * @param clientSocket The connecting client's socket.
     */
  void joinGame(string gameName, int clientSocket);

    /**
     * The method sends the gamesList to the client.
     * @param clientSocket The client's socket.
     */
  void sendGamesList(int clientSocket);

    /**
     * The method writes the given integer to the given socket.
     * @param clientSocket The given client socket.
     * @param num The given integer.
     */
  void writeInt(int clientSocket, int num);

    /**
     * The method transfers the to player of clientSocket the past move.
     * @param clientSocket The client's socket.
     * @param move The past move.
     */
  void playMove(int clientSocket, Point move);

  /**
   * The method writes the move to the clients.
   * @param writeSocket The client's socket number.
   * @param buffer The buffer which the move will be written to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or the end game value.
   */
  int writeMove(int writeSocket, Point buffer, size_t sizeBuffer);

    /**
     * The method returns the number of games that are open to be joined.
     * @return The number of games that are open to be joined.
     */
  int getAvailableGames();

    /**
     * The method returns the size of the gamesList.
     * @return The size of the gamesList.
     */
  int size();

    /**
     * The method checks the that the read/write to socket works and prints an
     * appropriate message.
     * @param numCheck The parameter received from the read/write to socket.
     * @param error The error message to be printed.
     * @return The numCheck.
     */
  ssize_t checkWriteErrors(ssize_t numCheck, string error);
};

#endif //OTHELLO_SERVERGAMES_H