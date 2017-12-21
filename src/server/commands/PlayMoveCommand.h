#ifndef OTHELLO_PLAYMOVECOMMAND_H
#define OTHELLO_PLAYMOVECOMMAND_H

#include "Command.h"
class PlayMoveCommand : public Command {
 public:
  explicit PlayMoveCommand(Server *server1): Command(server1){}
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_PLAYMOVECOMMAND_H
