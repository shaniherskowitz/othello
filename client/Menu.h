//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_MENU_H
#define OTHELLO_MENU_H
#define DEF_SIZE 8
#include "GameUI.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
#include "Client.h"

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

  int connectToServer(Client clinet, GameUI *print);

};

#endif //OTHELLO_MENU_H
