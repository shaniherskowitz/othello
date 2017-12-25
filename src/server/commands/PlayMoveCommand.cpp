//
// Created by shani herskowitz on 12/17/17.
//

#include "PlayMoveCommand.h"
#include <sstream>
void PlayMoveCommand::execute(vector<string> args) {
  if (args.size() != 4) return;
  stringstream geek(args[0]);
  int socket = 0;
  geek >> socket;
  char c = args[2][1];
  int x = c - '0';
  char c2 = args[3][0];
  int y = c2 - '0';
  if (x > 9 || x < 0 || y > 9 || y < 0) {
    x = -1;
    y = -1;
  }

  server->playMove(socket, Point(x, y));
}