//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_ENDGAMECOMMAND_H
#define OTHELLO_ENDGAMECOMMAND_H

#include "Command.h"
/**
 * Defining a EndGameCommand class to end the current game in gameRoom.
 */
class EndGameCommand: public Command {
 public:
    /**
     * The EndGameCommand's constructor.
     * @param server1 The game server.
     */
  explicit EndGameCommand(ServerGames *server1): Command(server1){}

    /**
     * The method executes an end game command meaning it closes the player's
     * connections.
     * @param args
     */
  virtual void execute(vector<string> args);
};

#endif //OTHELLO_ENDGAMECOMMAND_H
