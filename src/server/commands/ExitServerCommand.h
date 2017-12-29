#ifndef OTHELLO_EXITSERVERCOMMAND_H
#define OTHELLO_EXITSERVERCOMMAND_H

#include "Command.h"
/**
 * Defining an ExitServerCommand class to close the connection with the server.
 */
class ExitServerCommand : public Command {
 public:
  /**
   * The ExitServerCommand disconnect the connection with all sockets.
   * @param server1 The game server.
   */
  explicit ExitServerCommand(ServerGames *server1) : Command(server1) {}

  /**
   * The method executes the exit server command to disconnect all sockets.
   * @param args
   */
  virtual void execute(vector<string> args);

};

#endif //OTHELLO_EXITSERVERCOMMAND_H
