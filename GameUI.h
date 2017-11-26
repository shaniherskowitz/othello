//
// Created by shani herskowitz on 11/20/17.
//

#ifndef OTHELLO_GAMEUI_H
#define OTHELLO_GAMEUI_H

#include <vector>
#include "Move.h"
#include "Score.h"
class GameUI {
 public:
  /**
   * create object for printing in the game, for GUI or console.
   */
  GameUI() {

  }
  virtual ~GameUI() {

  }
  /**
   * ask user for input.
   */
  virtual void userInput() const = 0;
  /**
   * lets user know theres problem with input.
   */
  virtual void problemWithInput() const = 0;
  /**
   * @param board to print.
   * @param size of boards col, row.
   * prints the board to the screen.
   */
  virtual void printBoard(Board &board, int size) const = 0;
  /**
   * ask user to enter move again
   */
  virtual void repeatUserInput() const = 0;
  /**
   * @param symbol of player.
   * @param moves player can move.
   * prints all available user moves.
   */
  virtual void printMoves(char symbol, vector<Move> &movesList) const = 0;
  /**
   *
   * @param player1 symbol to count on board.
   * @param player2 symbol to count on board.
   * @param score to check who won.
   * declares the winner of the game.
   */
  virtual void declareWinner(char player1, char player2, Score const &score, Tile one, Tile two) const = 0;

  virtual void showMenu() const = 0;

  virtual void gameStart(int choice) const = 0;

  virtual void movesListIsEmpty() const = 0;

  virtual void computerMove(Point p) const = 0;

};

#endif //OTHELLO_GAMEUI_H
