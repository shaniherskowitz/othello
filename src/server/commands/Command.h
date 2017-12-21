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
  Server *server;
 public:
  explicit Command(Server *server1);
  virtual void execute(vector<string> args) = 0;
  virtual ~Command() {}

};

#endif //OTHELLO_COMMAND_H
