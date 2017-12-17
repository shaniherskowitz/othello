//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_GAMEROOM_H
#define OTHELLO_GAMEROOM_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include "Point.h"
#include <cstdlib>
#include <strings.h>
#define END_GAME -2
#define FREE_ROOM -5
#define IN_PROGRESS 0

using namespace std;

class GameRoom {

  bool started;
  int playerSocket1;
  int playerSocket2;
  string name;

 public:
  GameRoom(int playerSocket1, const string &name);
  void connectPlayer2(int playerSocket);
  const string getName() const;
  bool isStarted() const;
  void startGame();
  /**
   * The method initializes the player who is a client.
   * @param playerSocket The player's socket number.
   * @param playerNum A number to represent the symbol of the player.
   */
  void initializingPlayer(int playerSocket, int playerNum);
  void closeGame();
  int getOtherSocket(int playerSocket);

};

#endif //OTHELLO_GAMEROOM_H
