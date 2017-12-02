//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include <iostream>
#include "Point.h"

Point::Point(int xVal, int yVal) {
  x = xVal;
  y = yVal;
}

Point::Point() { Point(-1, -1); }

Point::~Point() {}

const int Point::getX() const { return this->x; }

const int Point::getY() const { return this->y; }

ostream &operator<<(ostream &os, Point const &point) {
  return cout << "(" << point.x << "," << point.y << ") ";
}

bool Point::operator==(const Point &point) const {
  return (point.x == this->x && point.y == this->y);
}

bool Point::operator!=(const Point &point) const {
  return !(point.x == this->x && point.y == this->y);
}

