//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_LISTGAMESCOMMAND_H
#define OTHELLO_LISTGAMESCOMMAND_H

#include "Command.h"
class ListGamesCommand : public Command {
 public:
  explicit ListGamesCommand(vector<GameRoom> gamesList): Command(gamesList){}
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_LISTGAMESCOMMAND_H
