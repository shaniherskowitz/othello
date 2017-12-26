//
// Created by shani herskowitz on 12/18/17.
//

#ifndef OTHELLO_REMOTEPLAYERMENU_H
#define OTHELLO_REMOTEPLAYERMENU_H

#include "Game.h"
class RemotePlayerMenu {
  GameUI *print;
 public:
  RemotePlayerMenu(GameUI *print1);
  Game *getGame();
  int connectToServer();
  void connectToRoom(int socket);
  void sendCommand(int socket, string command, string args);
  void getGamesListHelper(int socket, int size, vector<string> *gamesList);
  void getGamesList(int socket, vector<string> *gamesList);
  int readNum(int socket);
    int getChoice();
    void checkSocketConnection(ssize_t bytesWritten);
    void getAvailableGames(int socket);
    void sendStartCommand(int socket, vector<string> gamesList);
    bool isInGamesList(vector<string> gamesList, string gameName);
    void sendJoinCommand(int socket, vector<string> gamesList);
};

#endif //OTHELLO_REMOTEPLAYERMENU_H
