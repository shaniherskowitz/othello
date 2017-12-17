//
// Created by shani herskowitz on 12/17/17.
//

#include <cstring>
#include "Command.h"
Command::Command(vector<GameRoom> gamesList) {
  this->gamesList = gamesList;
}

vector<GameRoom>::iterator Command::getGameRoom(string gameName) {
  vector<GameRoom>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if (strcmp(gameName, it->getName()) == 0) return it;
    it++;
  }
  return it;
}
