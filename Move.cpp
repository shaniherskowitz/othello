//
// Created by shani herskowitz on 11/18/17.
//

#include "Move.h"

Move::Move(Point move) {
  this->move = Point(move);
  this->scoreCounter = 0;
}

Move::Move(Point move, int counter) {
  this->move = Point(move);
  this->scoreCounter = counter;
}

void Move::updateCounter(int counter) {
  this->scoreCounter += counter;
}
int Move::getScoreCounter() const {
  return scoreCounter;
}
Point Move::getPoint() const{
  return move;
}
void Move::mergeMove(Move other) {
  this->scoreCounter += other.scoreCounter;
}

