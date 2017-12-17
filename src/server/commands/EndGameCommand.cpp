//
// Created by shani herskowitz on 12/17/17.
//

#include "EndGameCommand.h"
void EndGameCommand::execute(vector<string> args) {
  if (args.empty()) return;
  vector<GameRoom>::iterator gameRoom = getGameRoom(args[0]);
  if (gameRoom == gamesList.end()) return;
  gameRoom->closeGame();
  gamesList.erase(gameRoom);
}
