//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_GAMELOGIC_H
#define OTHELLO_GAMELOGIC_H
#include "Player.h"
#include "Move.h"
#include "GameStatus.h"
class GameLogic {
 public:
  /**
  * create object for printing in the game, for GUI or console.
  */
  GameLogic() {

  }
  virtual ~GameLogic() {

  }
  virtual GameStatus turn(Player &player, Board &board, GameUI *print) = 0;
  virtual vector<Move> getMovesList(Tile player, Board &board) = 0;
  virtual void flipTiles(Board& board, Tile tile, Point location) const = 0;

};

#endif //OTHELLO_GAMELOGIC_H
