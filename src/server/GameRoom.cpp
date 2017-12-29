#include "GameRoom.h"

GameRoom::GameRoom(int playerSocket1, const string &name)
    : started(false), playerSocket1(playerSocket1), name(name) {}

GameRoom::~GameRoom() {}

void GameRoom::connectPlayer2(int playerSocket) {
  playerSocket2 = playerSocket;
  started = true;
}
const string &GameRoom::getName() const { return name; }

bool GameRoom::isStarted() const { return started; }

void GameRoom::startGame() {
  initializingPlayer(playerSocket1, 0);
  initializingPlayer(playerSocket2, 1);
}

void GameRoom::initializingPlayer(int playerSocket, int playerNum) {
  ssize_t x = write(playerSocket, &playerNum, sizeof(int));
  checkSocketConnection(x, "Error initializing player");
}

void GameRoom::closeGame() {
  if (started) {
  Point endGame(-2, -2);
  ssize_t x = write(playerSocket1, &endGame, sizeof(Point));
  if (x == -1) {
    checkSocketConnection(x, "Error closing gameRoom game");
    return;
  }
  close(playerSocket1);
    x = write(playerSocket2, &endGame, sizeof(Point));
    if (x == -1) {
      checkSocketConnection(x, "Error closing gameRoom game");
      return;
    }
    close(playerSocket2);
  } else {
    int endGame = -1;
    ssize_t x = write(playerSocket1, &endGame, sizeof(int));
    if (x == -1) {
      checkSocketConnection(x, "Error closing gameRoom game");
      return;
    }
    close(playerSocket1);
  }
}

int GameRoom::getOtherSocket(int playerSocket) {
  if (playerSocket1 == playerSocket) return playerSocket2;
  return playerSocket1;
}

bool GameRoom::playingInGame(int playerSocket) {
  return (playerSocket == playerSocket1 || playerSocket == playerSocket2);
}

void GameRoom::checkSocketConnection(ssize_t n, string msg) {
  if (n == -1) {
    cout << msg << endl;
    cout << "Socket disconnecting" << endl;
  }
}