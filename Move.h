//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_MOVE_H
#define OTHELLO_MOVE_H

#include "Point.h"
class Move {
  Point move;
  int scoreCounter;
 public:
  explicit Move(Point move);
  Move(Point move, int counter);
  void updateCounter(int counter);
  Point getPoint() const;
  void mergeMove(Move other);
  int getScoreCounter() const;
    bool operator==(const Move& move) const;

};

#endif //OTHELLO_MOVE_H
