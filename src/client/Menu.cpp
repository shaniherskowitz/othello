#include <limits>
#include <cstdlib>
#include "Menu.h"

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
  ifstream inFile;
  inFile.open("../exe/clientFiles/clientSettings");
  string x;
  int port = 0;
  if (!inFile) {
    cerr << "Unable to open file";
    exit(1);   // call system to stop
  }
  while (inFile >> x) {
    if (x == "serverPort:") {
      inFile >> x;

      stringstream geek(x); //not sure we are allowed to use
      geek >> port;
    }
    if (x == "serverIP:") {
      inFile >> x;
    }
  }
  const char *IP = x.c_str();
  inFile.close();

  Client client(IP, port);
  try {
    client.connectToServer();
    print->serverConnected();
  } catch (const char *msg) {
    print->serverConnectError(msg);
    exit(-1);
  }
  ssize_t n;
  int player;
  print->waitingForPlayer();
  n = read(client.getClientSocket(), &player, sizeof(int));
  if (n == -1) {
    print->socketReadError();
    exit(-1);
  }

  if (player == 0)
    return new Game(new RemotePlayer(Tile(X), client.getClientSocket(), true),
                    new RemotePlayer(oppositeSymbol(Tile(X)), client.getClientSocket(), false), print, 8);
  else
    return new Game(new RemotePlayer(Tile(X), client.getClientSocket(), false),
                    new RemotePlayer(oppositeSymbol(Tile(X)), client.getClientSocket(), true), print, 8);
}

Tile oppositeSymbol(Tile tile) {
  if (tile == X) return O;
  if (tile == O) return X;
  return EMPTY;
}