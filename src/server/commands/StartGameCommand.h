//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_STARTGAMECOMMAND_H
#define OTHELLO_STARTGAMECOMMAND_H

#include "Command.h"

/**
 * Defining a StartGameCommand class to define a game.
 */
class StartGameCommand : public Command {
 public:
    /**
     * The StartGameCommand constructor.
     * @param server1 The game server.
     */
  explicit StartGameCommand(ServerGames *server1) : Command(server1) {}

    /**
     * The method executes the startGame command 
     * @param args
     */
  virtual void execute(vector<string> args);
};

#endif //OTHELLO_STARTGAMECOMMAND_H
