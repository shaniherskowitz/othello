//
// Created by shani herskowitz on 12/17/17.
//

#include "JoinGameCommand.h"
#include <sstream>
void JoinGameCommand::execute(vector<string> args) {
  if (args.size() != 2) return;
  stringstream geek(args[1]);
  int socket = 0;
  geek >> socket;
  //server->joinGame(args[0],socket);
}