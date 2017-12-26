#include <cstring>
#include "ServerGames.h"
pthread_mutex_t count_mutex;

ServerGames *ServerGames::instance = NULL;

ServerGames *ServerGames::Instance() {
  if (!instance) instance = new ServerGames();
  return instance;
}

ServerGames::~ServerGames() {
  delete instance;
}

void ServerGames::deleteInstance() {
  ServerGames *instance = Instance();
  delete instance;
  instance = NULL;
}

vector<GameRoom>::iterator ServerGames::getGame(string gameName) {
  vector<GameRoom>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if (it->getName() == gameName) return it;
    it++;
  }
  return it;
}

void ServerGames::newGame(string gameName, int clientSocket) {
  if (getGame(gameName) != gamesList.end()) {
    int gameExists = -1;
    write(clientSocket, &gameExists, sizeof(gameExists));
  }
  GameRoom *gameRoom = new GameRoom(clientSocket, gameName);
  pthread_mutex_trylock(&count_mutex);
  gamesList.push_back(*gameRoom);
  pthread_mutex_unlock(&count_mutex);
}

void ServerGames::eraseGame(string gameName) {
  vector<GameRoom>::iterator gameRoom = getGame(gameName);
  if (gameRoom != gamesList.end()) {
    gameRoom->closeGame();
    gamesList.erase(gameRoom);
  }
}

void ServerGames::closeGames() {
  vector<GameRoom>::iterator it = gamesList.begin();
  if (it != gamesList.end()) {
    it->closeGame();
    it = gamesList.erase(it);
    it++;
  }
}

void ServerGames::joinGame(string gameName, int clientSocket) {
  vector<GameRoom>::iterator gameRoom = getGame(gameName);
  if (gameRoom != gamesList.end() && !gameRoom->isStarted()) {
    pthread_mutex_trylock(&count_mutex);
    gameRoom->connectPlayer2(clientSocket);
    gameRoom->startGame();
    pthread_mutex_unlock(&count_mutex);
  }
}

int ServerGames::sendGamesList(int clientSocket) {
  int numWords = getAvailableGames();
  writeInt(clientSocket, numWords);
  vector<GameRoom>::iterator it = gamesList.begin();
  while (it != gamesList.end()) {
    if (it->isStarted()) {
      it++;
      continue;
    }
    string game = it->getName();
    unsigned long gameSize = game.size();
    writeInt(clientSocket, gameSize);
    for (int i = 0; i < gameSize; i++) {
      char send = game[i];
      ssize_t w = write(clientSocket, &send, sizeof(char));
      checkWriteErrors((int) w, "Error writing gamesList to player");
    }
    it++;
  }
}

int ServerGames::getAvailableGames() {
  int count = 0;
  for (int i = 0; i < gamesList.size(); ++i) {
    if (!gamesList[i].isStarted()) count++;
  }
  return count;
}

void ServerGames::playMove(int clientSocket, Point move) {
  for (int i = 0; i < gamesList.size(); i++) {
    if (gamesList[i].playingInGame(clientSocket)) {
      GameRoom *gameRoom = &gamesList[i];
      writeMove(gameRoom->getOtherSocket(clientSocket), move, sizeof(move));
      break;
    }
  }
}

int ServerGames::writeMove(int writeSocket, Point buffer, size_t sizeBuffer) {
  if (buffer.getX() == END_GAME) return END_GAME;
  ssize_t w = write(writeSocket, &buffer, sizeBuffer);
  checkWriteErrors((int) w, "Error getting move from player");
  return (int) w;
}

void ServerGames::writeInt(int clientSocket, int num) {
  ssize_t w = write(clientSocket, &num, sizeof(num));
  checkWriteErrors((int) w, "Error writing gamesList to player");

}

int ServerGames::size() {
  return (int) gamesList.size();
}

int ServerGames::checkWriteErrors(int numCheck, string error) {
  if (numCheck == -1) {
    cout << error << endl;
    return numCheck;
  }
  if (numCheck == 0) {
    cout << "Player disconnected" << endl;
    return numCheck;
  }
}

int ServerGames::getPlayerCount() {
  int count = 0;
  for (int i = 0; i < gamesList.size(); ++i) {
    if (gamesList[i].isStarted()) count += 2;
    count += 1;
  }
  return count;
}

GameRoom ServerGames::findClientGame(int socket) {
  for (int i = 0; i < gamesList.size(); ++i) {
    if (gamesList[i].playingInGame(socket)) return gamesList[i];
  }
  //return NULL;
}