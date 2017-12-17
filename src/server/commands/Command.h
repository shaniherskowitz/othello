//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_COMMAND_H
#define OTHELLO_COMMAND_H
#include <vector>
#include <string>
#include "../Server.h"

using namespace std;

class Command {
 protected:
    vector<GameRoom> gamesList;
 public:
  explicit Command(vector<GameRoom> gamesList);
  virtual void execute(vector<string> args) = 0;
  virtual ~Command() {}

};

#endif //OTHELLO_COMMAND_H
