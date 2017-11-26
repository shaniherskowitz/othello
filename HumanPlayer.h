//
// Created by shani herskowitz on 11/20/17.
//

#ifndef OTHELLO_HUMANPLAYER_H
#define OTHELLO_HUMANPLAYER_H

#include "Player.h"
class HumanPlayer: public Player {
 public:
  explicit HumanPlayer(Tile symbol);
  ~HumanPlayer();


  virtual Move getTurnsMove(vector<Move> movesList, GameUI *print, Board& board);
  Move getUserInput(GameUI* gameUI) const;
  bool inMoves(Move move, vector<Move> moves) const;
};

#endif //OTHELLO_HUMANPLAYER_H
