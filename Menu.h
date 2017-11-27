//
// Created by shani herskowitz on 11/22/17.
//

#ifndef OTHELLO_MENU_H
#define OTHELLO_MENU_H

#include "GameUI.h"

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

};

#endif //OTHELLO_MENU_H
