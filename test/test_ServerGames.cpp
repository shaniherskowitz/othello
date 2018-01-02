//
// Created by shani herskowitz on 1/2/18.
//

#include <gtest/gtest.h>
#include "../src/server/ServerGames.h"

//will print errors since server not connected

TEST(testList, test) {
  ServerGames *gamesList = ServerGames::Instance();
  gamesList->newGame("game1", 2);

  EXPECT_EQ(1, gamesList->getAvailableGames());
   gamesList->joinGame("game1", 3);

  EXPECT_EQ(0, gamesList->getAvailableGames());

  gamesList->newGame("game2", 6);

  EXPECT_EQ(1, gamesList->getAvailableGames());

  gamesList->lastCall = true;
  gamesList->deleteInstance();
}
TEST(testList, test2) {
  ServerGames *gamesList = ServerGames::Instance();
  gamesList->newGame("game1", 2);
  gamesList->newGame("game2", 3);
  gamesList->newGame("game3", 4);

  EXPECT_EQ(3, gamesList->getAvailableGames());


  gamesList->lastCall = true;
  gamesList->deleteInstance();
}