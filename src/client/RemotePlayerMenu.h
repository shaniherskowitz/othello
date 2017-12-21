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
  Game* getGame();
  int connectToServer();
  void connectToRoom(int socket);
  void sendCommand(int socket, string command, string args);
  void getGames(int socket);

};

#endif //OTHELLO_REMOTEPLAYERMENU_H
