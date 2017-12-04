//
// Created by shani herskowitz on 12/2/17.
//

#include <limits>
#include <unistd.h>
#include <string>
#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(Tile symbol, int socket) : Player(symbol), socket(socket) {}

RemotePlayer::RemotePlayer(Tile symbol) : Player(symbol) {}
RemotePlayer::~RemotePlayer() {}

Move RemotePlayer::getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board) {

    sendMovesList(movesList);
    if (movesList.empty()) {
        //print no moves
        return Move(Point());
    }
   /* int w = write(socket, &movesList, sizeof(movesList));
    if (w == -1) throw "Error writing moves list to socket";
    string move;
    int r = read(socket, &move, sizeof(move));
    if (r == -1) throw "Error reading move from socket";*/

}

/*void RemotePlayer::sendMovesList(vector<Move> movesList) const {
    vector<Move>::iterator it = movesList.begin();
    while (it != movesList.end()) {
        char *move = it->getPoint().toString();
        ssize_t w = write(socket, move, strlen(move) + 1);
        if (w == -1) throw "Error writing move to socket";
        it++;
    }
}*/

Move RemotePlayer::parseMove(string s) {
    int counter = 0;
    char num[10];
    for (int i = 0; i < s.length(); i++) {
        if(s[i] == ' ') continue;
        num[counter] = s[i];
        counter++;
    }
    //int x = stoi(num[0], 1);
}

Move RemotePlayer::readMove() {

}

Move RemotePlayer::writeMove() {

}

