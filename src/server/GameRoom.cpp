//
// Created by shani herskowitz on 12/17/17.
//

#include "GameRoom.h"
GameRoom::GameRoom(int playerSocket1, const string &name)
    : started(false), playerSocket1(playerSocket1), name(name) {}

void GameRoom::connectPlayer2(int playerSocket) {
  playerSocket2 = playerSocket;
  started = true;
}
const string &GameRoom::getName() const {
  return name;
}
bool GameRoom::isStarted() const {
  return started;
}

void GameRoom::startGame() {
  initializingPlayer(playerSocket1, 0);
  initializingPlayer(playerSocket2, 1);
}
void GameRoom::initializingPlayer(int playerSocket, int playerNum) {
  ssize_t x = write(playerSocket, &playerNum, sizeof(int));
  if (x == -1) {
    cout << "Error writing to socket" << endl;
    exit(1);
  }
}

void GameRoom::closeGame() {
  close(playerSocket1);
  close(playerSocket2);
}

int GameRoom::getOtherSocket(int playerSocket) {
  if (playerSocket1 == playerSocket) return playerSocket2;
  return playerSocket1;
}

bool GameRoom::playingInGame(int playerSocket) {
  return (playerSocket == playerSocket1 || playerSocket == playerSocket2);
}
