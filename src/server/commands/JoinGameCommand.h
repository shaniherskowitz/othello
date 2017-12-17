//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_JOINGAMECOMMAND_H
#define OTHELLO_JOINGAMECOMMAND_H

#include "Command.h"
class JoinGameCommand : public Command {
 public:
  explicit JoinGameCommand(vector<GameRoom> gamesList): Command(gamesList){}
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_JOINGAMECOMMAND_H
