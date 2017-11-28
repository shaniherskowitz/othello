//
// Created by shani herskowitz on 11/18/17.
//

#include <iostream>
#include "Point.h"

Point::Point(int one, int two) {
  x = one;
  y = two;
}

Point::Point() { Point(-1, -1); }

Point::~Point() {

}

const int Point::getX() const {
  return this->x;
}

const int Point::getY() const {
  return this->y;
}

ostream &operator<<(ostream &os, Point const &point) {
  return cout << "(" << point.x << "," << point.y << ") ";
}

bool Point::operator==(const Point &point) const {
  return (point.x == this->x && point.y == this->y);
}
bool Point::operator!=(const Point &point) const {
  return !(point.x == this->x && point.y == this->y);
}

