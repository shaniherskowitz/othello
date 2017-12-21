//
// Created by shani herskowitz on 12/17/17.
//

#include "CommandsManager.h"

CommandsManager::CommandsManager(Server *server) {
  commandsMap["start"] = new StartGameCommand(server);
  commandsMap["list_games"] = new ListGamesCommand(server);
  commandsMap["join"] = new JoinGameCommand(server);
  commandsMap["play"] = new PlayMoveCommand(server);
  commandsMap["close"] = new EndGameCommand(server);
}

void CommandsManager::executeCommand(string command, vector<string> args) {
  Command *commandObj = commandsMap[command];
  commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
  map<string, Command *>::iterator it;
  for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
    delete it->second;
  }
}