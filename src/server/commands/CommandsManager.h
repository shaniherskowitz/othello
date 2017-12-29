#ifndef OTHELLO_COMMANDSMANAGER_H
#define OTHELLO_COMMANDSMANAGER_H

#include <map>
#include "StartGameCommand.h"
#include "ListGamesCommand.h"
#include "JoinGameCommand.h"
#include "PlayMoveCommand.h"
#include "EndGameCommand.h"
#include "ExitServerCommand.h"

/**
 * Defining a CommandManager class to map the player's input to the correct
 * Command.
 */
class CommandsManager {
    map<string, Command *> commandsMap;
 public:
    /**
     * The CommandsManager constructor.
     * @param server The game server.
     */
  explicit CommandsManager(ServerGames *server);
    /**
     * The CommandManager's destructor.
     */
  ~CommandsManager();
    /**
     * The method calls to execute the right command.
     * @param command The user's command.
     * @param args The execute func's arguments.
     */
  void executeCommand(string command, vector<string> args);
};

#endif //OTHELLO_COMMANDSMANAGER_H
