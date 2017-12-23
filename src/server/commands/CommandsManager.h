//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_COMMANDSMANAGER_H
#define OTHELLO_COMMANDSMANAGER_H

#include <map>
#include "StartGameCommand.h"
#include "ListGamesCommand.h"
#include "JoinGameCommand.h"
#include "PlayMoveCommand.h"
#include "EndGameCommand.h"
class CommandsManager {
 public:
  CommandsManager(Server *server);
  ~CommandsManager();
  void executeCommand(string command, vector<string> args);
 private:
  map<string, Command *> commandsMap;
};

#endif //OTHELLO_COMMANDSMANAGER_H
