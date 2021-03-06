#include "Move.h"

Move::Move(Point move) {
  this->move = Point(move);
  this->scoreCounter = 0;
}
Move::Move() {
  Move(Point);
  this->scoreCounter = 0;
}

Move::Move(Point move, int counter) {
  this->move = Point(move);
  this->scoreCounter = counter;
}

void Move::updateCounter(int counter) { this->scoreCounter += counter; }

int Move::getScoreCounter() const { return scoreCounter; }

Point Move::getPoint() const { return move; }

void Move::mergeMove(Move other) { this->scoreCounter += other.scoreCounter; }

bool Move::operator==(const Move &move) const {
  return (this->move == move.move && this->scoreCounter == move.scoreCounter);
}

bool Move::operator<(const Move &move) const {
  if (this->move.getX() == move.move.getX()) {
    return (this->move.getY() < move.move.getY());
  }
  return (this->move.getX() < move.move.getX());
}