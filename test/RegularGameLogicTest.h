//
// Created by shani herskowitz on 11/24/17.
//

#ifndef OTHELLO_REGULARGAMELOGICTEST_H
#define OTHELLO_REGULARGAMELOGICTEST_H

#include "gtest/gtest.h"
#include "../RegularGameLogic.h"
using namespace std;
class RegularGameLogicTest: public testing::Test {
 public:
  RegularGameLogicTest(): logic() {}

 protected:
  RegularGameLogic logic;
};

#endif //OTHELLO_REGULARGAMELOGICTEST_H
