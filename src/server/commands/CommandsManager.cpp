//
// Created by shani herskowitz on 12/17/17.
//

#include "CommandsManager.h"

CommandsManager::CommandsManager(vector<GameRoom> gamesList) {
  this->gamesList = gamesList;
  commandsMap["start"] = new StartGameCommand(gamesList);
  commandsMap["list_games"] = new ListGamesCommand(gamesList);
  commandsMap["join"] = new JoinGameCommand(gamesList);
  commandsMap["play"] = new PlayMoveCommand(gamesList);
  commandsMap["close"] = new EndGameCommand(gamesList);
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
