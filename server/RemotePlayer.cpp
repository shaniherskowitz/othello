//
// Created by shani herskowitz on 12/2/17.
//

#include <limits>
#include <unistd.h>
#include <string>
#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(Tile symbol, int socket) : Player(symbol), socket(socket) {}

RemotePlayer::~RemotePlayer() {}

Move RemotePlayer::getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board) {
    if (movesList.empty()) {
        //print no moves
        return Move(Point());
    }
    int w = write(socket, &movesList, sizeof(movesList));
    if (w == -1) throw "Error writing moves list to socket";
    string move;
    int r = read(socket, &move, sizeof(move));
    if (r == -1) throw "Error reading move from socket";


}

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

Move RemotePlayer::getUserInput(GameUI *print) const {
    print->userInput();
    int i, j;
    while (true) {
        cin >> i >> j;
        if (!cin.fail()) break;
        print->problemWithInput();
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
    return Move(Point(i - 1, j - 1));
}

bool RemotePlayer::inMoves(Move move, vector<Move> movesList) const {
    vector<Move>::iterator it = movesList.begin();
    while (it != movesList.end()) {
        if (it->getPoint() == move.getPoint()) { return true; }
        it++;
    }
    return false;
}
