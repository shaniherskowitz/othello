//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_STARTGAMECOMMAND_H
#define OTHELLO_STARTGAMECOMMAND_H

#include "Command.h"
class StartGameCommand : public Command {
 public:
  explicit StartGameCommand(Server server1) : Command(server1) {}
  virtual void execute(vector<string> args);
};

#endif //OTHELLO_STARTGAMECOMMAND_H
