#include <cstring>
#include "ServerGames.h"

ServerGames::ServerGames() {}

vector<GameRoom>::iterator ServerGames::getGame(string gameName) {
    vector<GameRoom>::iterator it = this->gamesList.begin();
    while (it != gamesList.end()) {
       // if (strcmp(gameName, it->getName()) == 0) return it;
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
    vector<GameRoom>::iterator gameRoom = getGame(gameName);
    if (gameRoom != gamesList.end()) {
        gameRoom->connectPlayer2(clientSocket);
        gameRoom->startGame();
    }
}

void ServerGames::sendListGames(int clientSocket) {
    unsigned long  numWords = gamesList.size();
    writeInt(clientSocket, numWords);
    vector<GameRoom>::iterator it = this->gamesList.begin();
    while (it != gamesList.end()) {
        string game = it->getName();
        unsigned long gameSize = game.size();
        writeInt(clientSocket, gameSize);
        for (int i = 0; i < gameSize; i++) {
            ssize_t w = write(clientSocket, &game.at(i), sizeof(char));
            if (w == -1) {
                cout << "Error writing gamesList to player" << endl;
                return;
            } if (w == 0) {
                cout << "Player disconnected" << endl;
                return;
            }
        }
        it++;
    }
}

void ServerGames::writeInt(int clientSocket, int num) {
    ssize_t w = write(clientSocket, &num, sizeof(num));
    if (w == -1) {
        cout << "Error writing gamesList to player" << endl;
        return;
    } if (w == 0) {
        cout << "Player disconnected" << endl;
        return;
    }
}

int ServerGames::size() {
    return gamesList.size();
}