#include <limits>
#include <cstdlib>
#include "Menu.h"
#include "RemotePlayerMenu.h"

Menu::Menu() {}

Menu::~Menu() {}
Tile oppositeSymbol(Tile tile);

void Menu::showMenu() {
  Game *game;
  GameUI *print = new ConsolUI();
  int choice = getUserInput(print);

  if (choice == 1) game = new Game(new HumanPlayer(Tile(X)), new HumanPlayer(Tile(O)), print, DEF_SIZE);
  else if (choice == 2) game = new Game(new HumanPlayer(Tile(X)), new AIPlayer(Tile(O)), print, DEF_SIZE);
  else if (choice == 3) game = getServerGame(print);

  print->gameStart(choice);
  game->run();
  delete game;

}
int Menu::getUserInput(GameUI *print) {
  int choice = 0;
  print->showMenu();
  while (true) {
    cin >> choice;
    if (!cin.fail() && (choice == 2 || choice == 1 || choice == 3)) break;
    print->problemWithInput();
    cin.clear();
    cin.ignore(std::numeric_limits<int>::max(), '\n');
  }
  return choice;

}
Game *Menu::getServerGame(GameUI *print) {
  RemotePlayerMenu menu(print);
  return menu.getGame();
}

Tile oppositeSymbol(Tile tile) {
  if (tile == X) return O;
  if (tile == O) return X;
  return EMPTY;
}