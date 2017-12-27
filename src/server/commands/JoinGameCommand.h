//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_JOINGAMECOMMAND_H
#define OTHELLO_JOINGAMECOMMAND_H

#include "Command.h"

/**
 * Defining a JoinGameCommand class to add a player to a game.
 */
class JoinGameCommand : public Command {
 public:
    /**
     * The JoinGameCommand constructor.
     * @param server1 The game server.
     */
  explicit JoinGameCommand(ServerGames *server1): Command(server1){}

    /**
     * The method executes the join game command to add a player to an
     * un-started game.
     * @param args The execute func's arguments.
     */
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_JOINGAMECOMMAND_H
