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

/*ostream& operator<<(ostream& os, Point const & point){
  cout << "(" << point.x << ","<< point.y << ") ";
}*/

void Point::print() const {
  cout << "(";
  cout << x;
  cout << ",";
  cout << y;
  cout << ") ";
}

bool Point::operator==(const Point &point)  const {
  return (point.x == this->x && point.y == this->y);
}
bool Point::operator!=(const Point &point)  const {
  return !(point.x == this->x && point.y == this->y);
}
void Point::add(int num) {
  x = x + num;
  y = y + num;
}
void Point::update(int x1, int y1) {
  x = x1;
  y = y1;
};
