//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H
#include "RegularGameLogic.h"

class Game {
 private:
  Player *one;
  Player *two;
  GameUI *print;
  int size;

 public:
  Game(Player *one1, Player *two1,  GameUI *print1, int size1 = 8);
  ~Game();
 void run();

};

#endif //OTHELLO_GAME_H
