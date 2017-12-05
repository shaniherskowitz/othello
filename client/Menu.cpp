//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include <limits>
#include <cstdlib>
#include "Menu.h"

Menu::Menu() {}

Menu::~Menu() {}
Tile oppositeSymbol(Tile tile);

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
    Client client("127.0.0.1", 8000);
    try {
      client.connectToServer();
      print->serverConnected();
    } catch (const char *msg) {
      print->serverConnectError(msg);
      exit(-1);
    }
    int n, player;
    print->waitingForPlayer();
    n = read(client.getClientSocket(), &player, sizeof(int));
    if (n == -1) {
      print->socketReadError();
      exit(-1);
    }

    if (player == 1)
      game = new Game(new RemotePlayer(Tile(X), client.getClientSocket(), true),
                      new RemotePlayer(oppositeSymbol(Tile(X)), client.getClientSocket(), false), print, DEF_SIZE);
    else
      game = new Game(new RemotePlayer(Tile(X), client.getClientSocket(), false),
                      new RemotePlayer(oppositeSymbol(Tile(X)), client.getClientSocket(), true), print, DEF_SIZE);
  }

  print->gameStart(choice);
  game->run();
  delete game;

}
int Menu::connectToServer(Client client, GameUI *print) {
  try {
    client.connectToServer();
  } catch (const char *msg) {
    print->serverConnectError(msg);
    exit(-1);
  }
  int n, player;
  print->waitingForPlayer();
  n = read(client.getClientSocket(), &player, sizeof(int));
  if (n == -1) {
    print->socketReadError();
    exit(-1);
  }
  return player;
}

Tile oppositeSymbol(Tile tile) {
  if (tile == X) return O;
  if (tile == O) return X;
  return EMPTY;
}