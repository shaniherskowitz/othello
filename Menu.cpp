//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include <limits>
#include "Menu.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
Menu::Menu() {}

Menu::~Menu() {}

void Menu::showMenu() {
  int choice = 0;
  Game *game;
  GameUI *print = new ConsolUI();
  print->showMenu();

  while (true) {
    cin >> choice;
    if (!cin.fail() && (choice == 2 || choice == 1 || choice == 3)) break;
    print->problemWithInput();
    cin.clear();
    cin.ignore(std::numeric_limits<int>::max(), '\n');
  }

  if (choice == 1) game = new Game(new HumanPlayer(Tile(X)), new HumanPlayer(Tile(O)), print, DEF_SIZE);
  else if (choice == 2) game = new Game(new HumanPlayer(Tile(X)), new AIPlayer(Tile(O)), print, DEF_SIZE);
  else if (choice == 3) game = new Game(new HumanPlayer(Tile(X)), new RemotePlayer(Tile(O)), print, DEF_SIZE);
  else return;

  print->gameStart(choice);

  game->run();

  delete game;

}