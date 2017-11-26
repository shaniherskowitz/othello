//
// Created by shani herskowitz on 11/24/17.
//

#ifndef OTHELLO_PLAYERTEST_H
#define OTHELLO_PLAYERTEST_H

#include "gtest/gtest.h"
#include "../Player.h"
#include <iostream>
using namespace std;
class AIPlayerTest: public testing::Test {
 public:
  AIPlayerTest(): player1(Tile(O)) {}

 protected:
  AIPlayer player1;
};

#endif //OTHELLO_PLAYERTEST_H
