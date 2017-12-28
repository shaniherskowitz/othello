#ifndef OTHELLO_OTHELLO_SERVERGAMES_H
#define OTHELLO_OTHELLO_SERVERGAMES_H

#include <vector>
#include "GameRoom.h"

class ServerGames {
  static ServerGames *instance;
  vector<GameRoom> gamesList;
  ServerGames() {};
  ServerGames(ServerGames &serverGames1) {};
  ServerGames &operator=(ServerGames const &) {};
  ~ServerGames();
 public:
  static ServerGames *Instance();
  static void deleteInstance();
  void closeGames();
  vector<GameRoom>::iterator getGame(string gameName);
  void eraseGame(string gameName);
  void newGame(string gameName, int clientSocket);
  void joinGame(string gameName, int clientSocket);
  int sendGamesList(int clientSocket);
  void writeInt(int clientSocket, int num);
  void playMove(int clientSocket, Point move);
  /**
   * The method writes the move to the clients.
   * @param writeSocket The client's socket number.
   * @param buffer The buffer which the move will be written to.
   * @param sizeBuffer The buffer's size.
   * @return The move value, or the end game value.
   */
  int writeMove(int writeSocket, Point buffer, size_t sizeBuffer);
  int getAvailableGames();
  int size();
  int checkWriteErrors(ssize_t numCheck, string error);
  int getPlayerCount();
  GameRoom findClientGame(int socket);
};

#endif //OTHELLO_SERVERGAMES_H