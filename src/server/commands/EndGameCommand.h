//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_ENDGAMECOMMAND_H
#define OTHELLO_ENDGAMECOMMAND_H

#include "Command.h"
class EndGameCommand: public Command {
 public:
  explicit EndGameCommand(Server *server1): Command(server1){}
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_ENDGAMECOMMAND_H
