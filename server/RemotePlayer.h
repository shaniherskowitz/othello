//
// Created by shani herskowitz on 12/2/17.
//

#ifndef OTHELLO_REMOTEPLAYER_H
#define OTHELLO_REMOTEPLAYER_H

#include "Player.h"
class RemotePlayer : public Player  {
    int socket;
    Move getUserInput(GameUI *print) const ;
    bool inMoves(Move move, vector<Move> movesList) const;
 public:
   RemotePlayer(Tile tile, int socket);
  ~RemotePlayer();
   Move getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board);
};

#endif //OTHELLO_REMOTEPLAYER_H
