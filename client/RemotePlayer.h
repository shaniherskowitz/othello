//
// Created by shani herskowitz on 12/2/17.
//

#ifndef OTHELLO_REMOTEPLAYER_H
#define OTHELLO_REMOTEPLAYER_H

#include "HumanPlayer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define NOT_INDEX -1
class RemotePlayer : public HumanPlayer {
  int socket;
  bool localTurn;

  Move writeMove(GameUI* print, vector<Move> movesList);
  Move readMove(GameUI* print);
 public:
  RemotePlayer(Tile tile, int socket, bool localTurn1);
  RemotePlayer(Tile tile, bool localTurn1);
  ~RemotePlayer();
  Move getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board);
};

#endif //OTHELLO_REMOTEPLAYER_H
