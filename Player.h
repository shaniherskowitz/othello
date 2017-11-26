//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H
#include <vector>
#include "Point.h"
#include "Move.h"
#include "ConsolUI.h"

class Player {
 protected:
  Tile symbol;
 public:
  explicit Player(Tile name);
  virtual ~Player();
  /**
   *
   * @return the players symbol.
   */
  Tile getSymbol() const;
  /**
   *
   * @param print for player to output to screen in order to get move.
   * @return point player entered to move.
   */
  virtual Move getTurnsMove(std::vector<Move> movesList, GameUI *print ,Board &board) = 0;

  char getSymbolMeaning() const;

};

#endif //OTHELLO_PLAYER_H
