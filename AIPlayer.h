//
// Created by shani herskowitz on 11/22/17.
//

#ifndef OTHELLO_AIPLAYER_H
#define OTHELLO_AIPLAYER_H

#include "Player.h"
class AIPlayer : public Player {
 public:
  explicit AIPlayer(Tile symbol);
  ~AIPlayer();

  Move getTurnsMove(std::vector<Move> movesList, GameUI *print,Board &board);

  int simulateMove(Board *board, Move move);


};

#endif //OTHELLO_AIPLAYER_H
