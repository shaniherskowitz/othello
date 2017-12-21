#include "PlayMoveCommand.h"
#include <sstream>
void PlayMoveCommand::execute(vector<string> args) {
  if (args.size() != 4) return;
  stringstream geek(args[1]);
  int socket = 0;
  geek >> socket;
  stringstream geek1(args[2]);
  int x = 0;
  geek1 >> x;
  stringstream geek2(args[2]);
  int y = 0;
  geek2 >> y;
  server->playMove(args[0],socket, Point(x, y));
}