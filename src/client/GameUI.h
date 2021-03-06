
#ifndef OTHELLO_GAMEUI_H
#define OTHELLO_GAMEUI_H

#include <vector>
#include "Move.h"
#include "Score.h"
#include "GameStatus.h"

/**
 * Defining a GameUI interface for printing the game for GUI or console.
 */
class GameUI {
 public:
  /**
   * GameUI's default constructor.
   */
  GameUI() {}

  /**
   * GameUI default destructor.
   */
  virtual ~GameUI() {}

  /**
   * The method asks user for input.
   */
  virtual void userInput() const = 0;

  /**
   * The method lets the user know there's a problem with input.
   */
  virtual void problemWithInput() const = 0;

  /**
   * The method prints the given board.
   * @param The given board.
   */
  virtual void printBoard(Board &board) const = 0;

  /**
   * The method asks user to enter move again
   */
  virtual void repeatUserInput() const = 0;

  /**
   * The method prints the given player moves.
   * @param Th given players symbol.
   * @param movesListThe given moves.
   */
  virtual void printMoves(char symbol, vector<Move> &movesList) const = 0;

  /**
   * The method declares the game's winner.
   * @param board The game's board.
   * @param gameStatus The game status.
   */
  virtual void declareWinner(Board &board, GameStatus gameStatus) const = 0;

  /**
   * The menu prints the menu.
   */
  virtual void showMenu() const = 0;

  /**
   * The method prints the user's choice for menu option.
   * @param choice The user's choice of type of game.
   */
  virtual void gameStart(int choice) const = 0;

  /**
   * The method prints if the moves list is empty.
   */
  virtual void movesListIsEmpty() const = 0;

  /**
   * The method prints the move the computer chose.
   * @param p The moves point.
   */
  virtual void computerMove(Point p) const = 0;
  /**
   * The method prints the move the player chose.
   * @param p point player played
   * @param player that played
   */
  virtual void played(Point p, char player) const = 0;

  /**
   * The method prints an error message when player can"t connect to server.
   * @param msg The error message to print.
   */
  virtual void serverConnectError(const char *msg) const = 0;

  /**
   * The message prints that the server is connected.
   */
  virtual void serverConnected() const = 0;

  /**
   * The method print that the player is waiting for other player to connect.
   */
  virtual void waitingForPlayer() const = 0;

  /**
   * The method print that the player is waiting for the other player"s move.
   */
  virtual void waitingForPlayerMove() const = 0;

  /**
   * The method prints the menu for the remote player.
   */
  virtual void remotePlayerMenu() const = 0;

  /**
   * The method prints the given gameRoom's name.
   * @param game The given gameRoom's name.
   */
  virtual void printGameRoom(string game) const = 0;

  /**
   * The method prints that there are no more available games.
   */
  virtual void noAvailableGames() const = 0;

  /**
   * The method prints to choose a game.
   */
  virtual void getGames() const = 0;

  /**
   * The method prints the available games from the given gameList.
   * @param gamesList The gamesList.
   */
  virtual void getGameRooms(vector<string> gamesList) const = 0;

  /**
   * The method prints that the current game already exists.
   */
  virtual void gameExists() const = 0;

  /**
   * The method prints that the current game doesn't exist.
   */
  virtual void gameNotExists() const = 0;

  /**
   * The method prints the given message.
   * @param msg The given message.
   */
  virtual void displayMsg(string msg) const = 0;

};

#endif //OTHELLO_GAMEUI_H
