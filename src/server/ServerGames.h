#ifndef OTHELLO_OTHELLO_SERVERGAMES_H
#define OTHELLO_OTHELLO_SERVERGAMES_H

#include <vector>
#include "GameRoom.h"

class ServerGames {
    vector<GameRoom> gamesList;
public:
    ServerGames();
    vector<GameRoom>::iterator getGame(string gameName);
    void eraseGame(string gameName);
    void addGame(string gameName, int clientSocket);
    void joinGame(string gameName, int clientSocket);
    void sendListGames(int clientSocket);
    void writeInt(int clientSocket, int num);
    int size();
};

#endif //OTHELLO_SERVERGAMES_H