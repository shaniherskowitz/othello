#ifndef OTHELLO_LISTGAMESCOMMAND_H
#define OTHELLO_LISTGAMESCOMMAND_H

#include "Command.h"

/**
 * Defining a ListGamesCommand class to send the list of games to player.
 */
class ListGamesCommand : public Command {
 public:
    /**
     * The ListGamesCommand constructor.
     * @param server1 The game server.
     */
  explicit ListGamesCommand(ServerGames *server1): Command(server1){}

    /**
     * The method executes the the listGames command to send the gamesList to
     * the player.
     * @param args The execute func's arguments.
     */
  virtual void execute(vector<string> args);
};

#endif //OTHELLO_LISTGAMESCOMMAND_H
