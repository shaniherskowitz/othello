//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_GAMELOGIC_H
#define OTHELLO_GAMELOGIC_H
#include "Player.h"
#include "Move.h"
#include "GameStatus.h"

/**
 * Defining a GameLogic interface.
 */
class GameLogic {
 public:
  /**
  * The GameLogic's default constructor.
  */
  GameLogic() {}

  /**
   * The GameLogic's destructor.
   */
  virtual ~GameLogic() {}

  /**
   * The method plays a single player's turn.
   * @param player The player with the turn.
   * @param board The current board.
   * @param print The game gameUI.
   * @return The current game status.
   */
  virtual GameStatus turn(Player &player, Board &board, GameUI *print) = 0;

  /**
   * The method returns a list with the possible moves the player can play in
   * his turn.
   * @param player The players symbol.
   * @param board The game's board.
   * @return The moves list.
   */
  virtual vector<Move> getMovesList(Tile player, Board &board) = 0;

  /**
   * The method sets the given tile at the given point and flips the tiles
   * on the board according to the game logic.
   * @param board The game's board.
   * @param tile The tile to be set.
   * @param location The player's move.
   */
  virtual void flipTiles(Board &board, Tile tile, Point location) const = 0;

};

#endif //OTHELLO_GAMELOGIC_H
