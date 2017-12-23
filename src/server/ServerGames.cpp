#include <cstring>
#include "ServerGames.h"

ServerGames::ServerGames() {}

vector<GameRoom>::iterator ServerGames::getGame(string gameName) {
    vector<GameRoom>::iterator it = this->gamesList.begin();
    while (it != gamesList.end()) {
        if (strcmp(gameName, it->getName()) == 0) return it;
        it++;
    }
    return it;
}

void ServerGames::addGame(string gameName, int clientSocket) {
    if (getGame(gameName) != gamesList.end()) {
        int gameExists = -1;
        write(clientSocket, &gameExists, sizeof(gameExists));
    }
    GameRoom *gameRoom = new GameRoom(clientSocket, gameName);
    gamesList.push_back(*gameRoom);
}

void ServerGames::eraseGame(string gameName) {
    vector<GameRoom>::iterator gameRoom = getGame(gameName);
    if (gameRoom != gamesList.end()) {
        gamesList.erase(gameRoom);
    }
}

void ServerGames::joinGame(string gameName, int clientSocket) {
    if (getGame(gameName) != gamesList.end()) {

    }
}