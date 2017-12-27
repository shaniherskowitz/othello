//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_PLAYMOVECOMMAND_H
#define OTHELLO_PLAYMOVECOMMAND_H

#include "Command.h"

/**
 * Defining a PlayMoveCommand class.
 */
class PlayMoveCommand : public Command {
 public:
    /**
     * The PlayMoveCommand constructor.
     * @param server1 The game server.
     */
  explicit PlayMoveCommand(ServerGames *server1): Command(server1){}

    /**
     * The method executes the playMove command to send a game move to the
     * other player.
     * @param args The execute func's arguments.
     */
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_PLAYMOVECOMMAND_H
