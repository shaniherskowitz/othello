#include "EndGameCommand.h"
void EndGameCommand::execute(vector<string> args) {
  if (args.empty()) return;
  server->closeGames();

}
