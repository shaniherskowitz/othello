//
// Created by shani herskowitz on 12/26/17.
//

#include "ExitServerCommand.h"
void ExitServerCommand::execute(vector<string> args) {
  if (args.empty()) return;
  server->closeGames();
  Server::exitCondition();
}