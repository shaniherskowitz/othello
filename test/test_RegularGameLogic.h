//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_TEST_REGULARGAMELOGIC_H
#define OTHELLO_TEST_REGULARGAMELOGIC_H

#include "gtest/gtest.h"
#include "../RegularGameLogic.h"
using namespace std;
class test_RegularGameLogic : public testing::Test {
 public:
  test_RegularGameLogic() : logic() {}

 protected:
  RegularGameLogic logic;
};

#endif //OTHELLO_TEST_REGULARGAMELOGIC_H
