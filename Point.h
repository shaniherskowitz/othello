//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_POINT_H
#define OTHELLO_POINT_H
#include <ostream>
using namespace std;

class Point {
 private:
  int x;
  int y;

 public:
  /**
   *
   * @param one for x.
   * @param two for y.
   */
  Point(int one, int two);
  /**
    * The Point class default constructor.
    */
  Point();

  ~Point();
  /**
   *
   * @return  x.
   */
  const int getX() const;
  /**
   *
   * @return y.
   */
  const int getY() const;
  /**
   * the point.
   */
  //friend ostream& operator<<(ostream& os, Point const & point);
  /**
   *
   * @param point to check.
   * @return if both points are the same.
   */
  bool operator==(const Point &point) const;
  /**
   *
   * @param num to add to point.
   */

  bool operator!=(const Point &point)  const;

  void add(int num);

  void print() const;

  void update(int x1, int y1);

};

#endif //OTHELLO_POINT_H
