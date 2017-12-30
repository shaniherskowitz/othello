#ifndef OTHELLO_SCORE_H
#define OTHELLO_SCORE_H

#include "Board.h"
class Score {
 private:
  Board board;

 public:
  /**
   * The Score's constructor.
   * @param board1 To check the score of the game.
   */
  explicit Score(Board &board1);

    /**
     * The Score's destructor.
     */
  ~Score();

  /**
   *
   * @param player1 symbol
   * @param player2 symbol
   * @return checks witch symbol appears more on the board and returns the amount of each.
   */
  Point *checkScore(Tile player1, Tile player2) const;

};

#endif //OTHELLO_SCORE_H
