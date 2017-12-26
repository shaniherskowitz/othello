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
  virtual void socketReadError() const;
  virtual void socketWriteError() const;
  virtual void playerConnected(char tile) const;
  virtual void serverConnectError(const char *msg) const;
  virtual void serverConnected() const;
  virtual void waitingForPlayer() const;
  virtual void playerDisconnected() const;
  virtual void waitingForPlayerMove() const;
  virtual void remotePlayerMenu() const;
  virtual void printGameRoom(string game) const;
  virtual void noAvailableGames() const;
  virtual void getGames() const;
    virtual void getGameRooms(vector<string> gamesList) const;
    virtual void noOpenGames() const ;
    virtual void gameExists() const ;
    virtual void gameNotExists() const ;
    virtual void displayMsg(string msg const) const ;
};

#endif //OTHELLO_CONSOLUI_H
