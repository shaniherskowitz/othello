//
// Created by shani herskowitz on 12/2/17.
//

#include <limits>
#include <unistd.h>
#include "RemotePlayer.h"
#include "AIPlayer.h"

RemotePlayer::RemotePlayer(Tile symbol, int socket) : Player(symbol), socket(socket) {}

RemotePlayer::~RemotePlayer() {}

Move RemotePlayer::getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board) {
    int write = write(socket, &movesList, sizeof(movesList));
    if (write == -1) throw "Error writing moves list to socket";
    string move;
    int read = read(socket, &move, sizeof(move));
    if (read == -1) throw "Error reading move from socket";


    /*print->printBoard(board);
    if (movesList.empty()) {
        print->movesListIsEmpty();
        return Move(Point(NOT_INDEX, NOT_INDEX));
    }
    print->printMoves(getSymbolMeaning(), movesList);
    Move move = getUserInput(print);
    while (!inMoves(move, movesList)) {
        print->repeatUserInput();
        print->printMoves(getSymbolMeaning(), movesList);
        move = getUserInput(print);
    }
    return move;*/
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
