//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H
#include "RegularGameLogic.h"

/**
 * Defining a game class.
 */
class Game {
 private:
  Player *player1;
  Player *player2;
  GameUI *print;
  int size;

 public:
  /**
   * The Game's constructor.
   * @param one1 The first player.
   * @param two1 Te second player.
   * @param print1 The GameUI
   * @param size1 The game board's size.
   */
  Game(Player *one1, Player *two1, GameUI *print1, int size1 = 8);

  /**
   * The Game's destructor.
   */
  ~Game();

  /**
   * The method starts and runs the game.
   */
  void run();

};

#endif //OTHELLO_GAME_H
