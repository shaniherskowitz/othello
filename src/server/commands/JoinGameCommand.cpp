#include "JoinGameCommand.h"
#include <sstream>
void JoinGameCommand::execute(vector<string> args) {
  if (args.size() != 3) return;
  stringstream geek(args[0]);
  int socket = 0;
  geek >> socket;
  server->joinGame(args[2],socket);
}