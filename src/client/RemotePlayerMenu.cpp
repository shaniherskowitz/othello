//
// Created by shani herskowitz on 12/18/17.
//
#include "RemotePlayerMenu.h"
#include "RemotePlayer.h"
#include <sstream>
#include "Client.h"
#include <signal.h>
RemotePlayerMenu::RemotePlayerMenu(GameUI *print1) : print(print1) {}

void RemotePlayerMenu::connectToRoom(int socket) {
  print->remotePlayerMenu();
  int choice = getChoice();
  stringstream ss;
  ss << socket;
  string socketString = ss.str();
  vector<string> gamesList;
  getGamesList(socket, &gamesList);
  if (choice == 1) sendStartCommand(socket, gamesList);
  if (choice == 2) sendJoinCommand(socket, gamesList);
}

void RemotePlayerMenu::checkSocketConnection(ssize_t bytesWritten) {
  if (bytesWritten == -1) {
    print->displayMsg("Server is disconnecting");
    exit(1);
  }
  if (bytesWritten == 0) exit(1);
}

void RemotePlayerMenu::sendStartCommand(int socket, vector<string> gamesList) {
  print->displayMsg("Please enter a game name:");
  string command = "start";
  string gameName;
  cin >> gameName;
  while (isInGamesList(gamesList, gameName)) {
    print->gameExists();
    cin >> gameName;
  }
  sendCommand(socket, command, gameName);
  int gameCreated;
  ssize_t r = read(socket, &gameCreated, sizeof(gameCreated));
  checkSocketConnection(r);
  if (!gameCreated) {
    print->gameExists();
    sendStartCommand(socket, gamesList);
  }
}

bool RemotePlayerMenu::isInGamesList(vector<string> gamesList, string gameName) {
  vector<string>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if (gameName == *it) return true;
    it++;
  }
  return false;
}

void RemotePlayerMenu::sendJoinCommand(int socket, vector<string> gamesList) {
  if (gamesList.empty()) {
    print->noAvailableGames();
    print->displayMsg("To start a new game please enter start, to quit press any key:");
    string option;
    cin >> option;
    if (option != "start") exit(1);
    sendStartCommand(socket, gamesList);
    return;
  }
  print->getGames();
  print->getGameRooms(gamesList);
  string command = "join";
  string gameName;
  cin >> gameName;
  while (!isInGamesList(gamesList, gameName)) {
    print->gameNotExists();
    cin >> gameName;
  }
  sendCommand(socket, command, gameName);
}

int RemotePlayerMenu::getChoice() {
  int choice = 0;
  while (true) {
    cin >> choice;
    if (!cin.fail() && (choice == 2 || choice == 1)) break;
    print->problemWithInput();
    cin.clear();
    cin.ignore(std::numeric_limits<int>::max(), '\n');
  }
  return choice;
}
void RemotePlayerMenu::getGamesList(int socket, vector<string> *gamesList) {
  string command = "list_games";
  sendCommand(socket, command, "");
  unsigned numGames;
  ssize_t n = read(socket, &numGames, sizeof(numGames));
  checkSocketConnection(n);
  getGamesListHelper(socket, numGames, gamesList);
}

void RemotePlayerMenu::getGamesListHelper(int socket, int size, vector<string> *gamesList) {
  for (int i = 0; i < size; i++) {
    int gameNameSize = readNum(socket);
    char gameName[50];
    for (int j = 0; j < gameNameSize; j++) {
      char current;
      ssize_t n = read(socket, &current, sizeof(char));
      checkSocketConnection(n);
      gameName[j] = current;
    }
    gameName[gameNameSize] = '\0';
    gamesList->push_back(string(gameName));
  }
}

int RemotePlayerMenu::readNum(int socket) {
  int num;
  ssize_t n = read(socket, &num, sizeof(num));
  checkSocketConnection(n);
  return num;
}

void RemotePlayerMenu::sendCommand(int socket, string command, string args) {
  string send = command + " " + args;
  int sendSize = (int) send.size();
  signal(SIGPIPE, SIG_IGN);
  ssize_t n = write(socket, &sendSize, sizeof(int));
  checkSocketConnection(n);
  for (int i = 0; i < sendSize; i++) {
    n = write(socket, &send.at(i), sizeof(char));
    checkSocketConnection(n);
  }
}

int RemotePlayerMenu::connectToServer() {
  //Client *client = openFile();
  ifstream inFile;
  inFile.open("clientSettings");
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
    if (x == "serverIP:") inFile >> x;
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
  connectToRoom(client.getClientSocket());
  int clientSocket = client.getClientSocket();
  // delete(client);
  return clientSocket;
  //return client->getClientSocket();
}

Game *RemotePlayerMenu::getGame() {
  int socket = connectToServer();
  ssize_t n;
  int player;
  print->waitingForPlayer();
  n = read(socket, &player, sizeof(int));
  checkSocketConnection(n);
  if (player == 0)
    return new Game(new RemotePlayer(Tile(X), socket, true),
                    new RemotePlayer(Tile(O), socket, false), print, 8);
  else if (player == 1)
    return new Game(new RemotePlayer(Tile(X), socket, false),
                    new RemotePlayer(Tile(O), socket, true), print, 8);
  print->displayMsg("Server is disconnecting");
  delete print;
  exit(1);
}

Client RemotePlayerMenu::openFile() {
  ifstream inFile;
  inFile.open("clientSettings");
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
    if (x == "serverIP:") inFile >> x;
  }
  const char *IP = x.c_str();
  inFile.close();
  return Client(IP, port);
}