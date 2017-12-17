//
// Created by shani herskowitz on 12/17/17.
//

#include "StartGameCommand.h"
#include <sstream>
void StartGameCommand::execute(vector<string> args) {//need to make sure args not null
  if (args.size() != 2) return;
  stringstream geek(args[1]);
  int socket = 0;
  geek >> socket;
  server->newGame(args[0],socket);
}