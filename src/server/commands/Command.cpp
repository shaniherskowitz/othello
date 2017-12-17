//
// Created by shani herskowitz on 12/17/17.
//

#include "Command.h"
Command::Command(vector<GameRoom> gamesList) {
  this->gamesList = gamesList;
}

GameRoom Command::getGameRoom(string gameName) {
  vector<GameRoom>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if
  }
}
