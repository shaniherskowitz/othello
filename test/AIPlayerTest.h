//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_AIPLAYERTEST_H
#define OTHELLO_AIPLAYERTEST_H

#include "gtest/gtest.h"
#include "../client/Player.h"
#include <iostream>
using namespace std;
class AIPlayerTest : public testing::Test {
 public:
  AIPlayerTest() : player1(Tile(O)) {}

 protected:
  AIPlayer player1;
};

#endif //OTHELLO_AIPLAYERTEST_H
