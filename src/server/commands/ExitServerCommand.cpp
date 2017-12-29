#include "ExitServerCommand.h"
void ExitServerCommand::execute(vector<string> args) {
  if (!args.empty()) return;
  server->closeGames();
}