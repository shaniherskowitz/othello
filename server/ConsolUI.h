//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_CONSOLUI_H
#define OTHELLO_CONSOLUI_H

#include "Score.h"
#include "GameUI.h"
#include "GameStatus.h"
#include <vector>
class ConsolUI : public GameUI {
 public:
  /**
   * create object for printing in the game, for console.
   */
  ConsolUI();
  virtual ~ConsolUI();
  virtual void userInput() const;
  virtual void problemWithInput() const;
  virtual void printBoard(Board &board) const;
  virtual void repeatUserInput() const;
  virtual void printMoves(char symbol, vector<Move> &movesList) const;
  virtual void declareWinner(Board &board, GameStatus gameStatus) const;
  virtual void showMenu() const;
  virtual void gameStart(int choice) const;
  virtual void movesListIsEmpty() const;
  virtual void computerMove(Point p) const;
  virtual void played(Point p, char player) const;

};

#endif //OTHELLO_CONSOLUI_H