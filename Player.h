//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H
#include <vector>
#include "Point.h"
#include "Move.h"
#include "ConsolUI.h"

/**
 * Defining a Player interface.
 */
class Player {
 protected:
  Tile symbol;
 public:
    /**
     * The Player's construcotr.
     * @param name The player's symbol.
     */
  explicit Player(Tile name);

    /**
     * The Player's destructor.
     */
  virtual ~Player();

  /**
   * The method returns the player's symbol.
   * @return The players symbol.
   */
  Tile getSymbol() const;

  /**
   * The method gets the player's move from the given optional moves list.
   * @param movesList The optional moves list.
   * @param print The gameUI.
   * @param board The game's board.
   * @return The player's chosen move.
   */
  virtual Move getTurnsMove(std::vector<Move> movesList, GameUI *print ,Board &board) = 0;

    /**
     * The method returns the player's symbol in char.
     * @return The player's symbol.
     */
  char getSymbolMeaning() const;

};

#endif //OTHELLO_PLAYER_H
