//
// Created by shani herskowitz on 12/26/17.
//

#ifndef OTHELLO_EXITSERVERCOMMAND_H
#define OTHELLO_EXITSERVERCOMMAND_H

#include "Command.h"
class ExitServerCommand: public Command {
 public:
  explicit ExitServerCommand(ServerGames *server1): Command(server1){}
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_EXITSERVERCOMMAND_H
