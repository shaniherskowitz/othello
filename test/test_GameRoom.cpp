

#include <gtest/gtest.h>
#include "../src/server/GameRoom.h"
TEST(gameroom, test1) {
  GameRoom game1(2, "game1");

  EXPECT_EQ(false, game1.isStarted());
  game1.connectPlayer2(3);
  EXPECT_EQ(true, game1.isStarted());
}
TEST(gameroom, test2) {
  GameRoom game1(2, "game");
  game1.connectPlayer2(3);

  EXPECT_EQ(2, game1.getOtherSocket(3));
  EXPECT_EQ(3, game1.getOtherSocket(2));
}