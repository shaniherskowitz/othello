//
// Created by shani herskowitz on 12/2/17.
//

#ifndef OTHELLO_REMOTEPLAYER_H
#define OTHELLO_REMOTEPLAYER_H

#include "Player.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
class RemotePlayer : public Player {
  int socket;
  Move parseMove(string s);
  Move getUserInput(GameUI *print) const;
  void sendMovesList(vector<Move> movesList) const;
  bool inMoves(Move move, vector<Move> movesList) const;
  Move writeMove();
  Move readMove();
 public:
  RemotePlayer(Tile tile, int socket);
  RemotePlayer(Tile tile);
  ~RemotePlayer();
  Move getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board);
};

#endif //OTHELLO_REMOTEPLAYER_H
