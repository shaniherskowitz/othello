//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_MOVE_H
#define OTHELLO_MOVE_H

#include "Point.h"

/**
 * Defining a Move class.
 */
class Move {
  Point move;
  int scoreCounter;
 public:
  /**
   * The Move's constructor.
   * @param move The moves location.
   */
  explicit Move(Point move);
  /**
   * The Move's default constructor
   */
  Move();

  /**
   * The Move's constructor.
   * @param move The move's location.
   * @param counter The number of tiles it will flip given this move will
   * be chosen.
   */
  Move(Point move, int counter);

  /**
   * The method updates the move's scoreCounter.
   * @param counter The amount of additional tiles wil be flipped.
   */
  void updateCounter(int counter);

  /**
   * The method returns the moves location.
   * @return The move's location.
   */
  Point getPoint() const;

  /**
   * The method merges two moves with same location-merges the scoreCounter.
   * @param other The other move.
   */
  void mergeMove(Move other);

  /**
   * The method returns the score counter- the amount of tiles to be flipped.
   * @return The scoreCounter.
   */
  int getScoreCounter() const;

  /**
   * The method overloads the equals operator.
   * @param move The move to be cmpared to.
   * @return True if moves are equal, else false.
   */
  bool operator==(const Move &move) const;
};

#endif //OTHELLO_MOVE_H
