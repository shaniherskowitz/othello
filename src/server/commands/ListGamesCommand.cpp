//
// Created by shani herskowitz on 12/17/17.
//

#include "ListGamesCommand.h"
#include <sstream>
void ListGamesCommand::execute(vector<string> args) {
  if (args.empty()) return;
  stringstream geek(args[0]);
  int socket = 0;
  geek >> socket;
 // server->sendGamesList(socket);
}