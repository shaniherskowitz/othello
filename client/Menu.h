//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_MENU_H
#define OTHELLO_MENU_H
#include "GameUI.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
#include "Client.h"
#include <fstream>
#include <sstream>
#define DEF_SIZE 8
/**
 * Defining a Menu class.
 */
class Menu {
 public:
  /**
   * The Menu's default constructor.
   */
  Menu();

  /**
   * The Menu's destructor.
   */
  ~Menu();

  /**
   * The method starts a game according to the user's choice.
   */
  void showMenu();
  /**
   *
   * @param to print to user what to do
   * @return game with remote players based on if the client connected first.
   */
  Game *getServerGame(GameUI *print);
  /**
   *
   * @param print to user his options
   * @return the game the user selected
   */
  int getUserInput(GameUI *print);

};

#endif //OTHELLO_MENU_H
