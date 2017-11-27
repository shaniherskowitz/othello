//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_POINT_H
#define OTHELLO_POINT_H
#include <ostream>
using namespace std;

/**
 * Defining a Point class.
 */
class Point {
 private:
  int x;
  int y;

 public:
  /**
   * THe Point's constructor.
   * @param x The x value.
   * @param y The y value.
   */

  Point(int x, int y);

  /**
    * The Point's default constructor.
    */
  Point();

    /**
     * The Point's destructor.
     */
  ~Point();

  /**
   * The method returns the point's x value
   * @return  The x value.
   */
  const int getX() const;

  /**
   * The method returns the y value.
   * @return The y value.
   */
  const int getY() const;

  /**
   * the point.
   */
  //friend ostream& operator<<(ostream& os, Point const & point);
  /**
   * The method overloads the equals operator.
   * @param point The other point that is compared.
   * @return True if both points are equal, else false.
   */
  bool operator==(const Point &point) const;

  /**
   * The method overload the not-equals operator.
   * @param point The other point that is compared.
   * @return True if the points aren't equal and else false.
   */
  bool operator!=(const Point &point)  const;

  //void add(int num);

    /**
     * The methods prints the point.
     */
  void print() const;

  //void update(int x1, int y1);
};

#endif //OTHELLO_POINT_H
