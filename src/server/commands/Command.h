//
// Created by shani herskowitz on 12/17/17.
//

#ifndef OTHELLO_COMMAND_H
#define OTHELLO_COMMAND_H
#include <vector>
#include <string>
#include "../Server.h"

using namespace std;

/**
 * Defining a Command abstract class to execute a player's command.
 */
class Command {
 protected:
  ServerGames *server;
 public:
    /**
     * The Command's constructor.
     * @param server1 The serverGames object which performs the command on the
     * list of games.
     */
  explicit Command(ServerGames *server1);

    /**
     * The method execute the command with the given arguments.
     * @param args The arguent to the function presented as strings.
     */
  virtual void execute(vector<string> args) = 0;

    /**
     * The Command destructor.
     */
  virtual ~Command() {}
};

#endif //OTHELLO_COMMAND_H
