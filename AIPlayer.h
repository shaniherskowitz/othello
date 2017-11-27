//
// Created by shani herskowitz on 11/22/17.
//

#ifndef OTHELLO_AIPLAYER_H
#define OTHELLO_AIPLAYER_H

#include "Player.h"

/**
 * Defining an AIPLayer class which implements Player interface.
 */
class AIPlayer : public Player {
 public:
  /**
   * The AIPlayer class constructor.
   * @param symbol The player symbol.
   */
  explicit AIPlayer(Tile symbol);
  /**
   * The AIPlayer class destructor.
   */
  ~AIPlayer();

  Move getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board);

  /**
   * The method returns the score of the given move, which is calculated
   * according to the simulation of the other players moves.
   * @param board The current game board.
   * @param move The given move.
   * @return The move's score.
   */
  int simulateMove(Board *board, Move move);

};

#endif //OTHELLO_AIPLAYER_H
