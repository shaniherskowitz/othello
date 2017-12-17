//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_PLAYMOVECOMMAND_H
#define OTHELLO_PLAYMOVECOMMAND_H

#include "Command.h"
class PlayMoveCommand : public Command {
 public:
  explicit PlayMoveCommand(vector<GameRoom> gamesList): Command(gamesList){}
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_PLAYMOVECOMMAND_H
