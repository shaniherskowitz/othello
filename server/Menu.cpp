//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include <limits>
#include <cstdlib>
#include "Menu.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
#include "Server.h"

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
  else if (choice == 3) {
    Server server(8000);
    try {
      server.start();
    } catch (const char *msg) {
      cout << "Cannot start server. Reason: " << msg << endl;
      exit(-1);
    }
    //Server server(10000);
    //server.start();
    server.stop();
    //game = new Game(new HumanPlayer(Tile(X)), new RemotePlayer(Tile(O)), print, DEF_SIZE);
  }
  else return;

  print->gameStart(choice);

  game->run();

  delete game;

}