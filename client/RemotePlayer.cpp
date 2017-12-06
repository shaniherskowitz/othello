//
// Created by shani herskowitz on 12/2/17.
//

#include <limits>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(Tile symbol, int socket, bool localTurn1) :
    HumanPlayer(symbol), socket(socket), localTurn(localTurn1) {}

RemotePlayer::RemotePlayer(Tile symbol, bool localTurn1) : HumanPlayer(symbol), localTurn(localTurn1) {}
RemotePlayer::~RemotePlayer() {}

Move RemotePlayer::getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board) {
  print->printBoard(board);
  if (localTurn) return writeMove(print, movesList);
    return readMove(print);

}

Move RemotePlayer::readMove(GameUI *print) {
  int x, y;
  print->waitingForPlayerMove();
    x = readSocket(print);
    y = readSocket(print);
    /*if (x== -1) {
        print->movesListIsEmpty();
        cout << "no possible moves" << endl;
    }*/

  return Move(Point(x, y));
}

Move RemotePlayer::writeMove(GameUI* print, vector<Move> movesList) {
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
  int x = move.getPoint().getX(), y = move.getPoint().getY();
    writeSocket(x, sizeof(x), print);
    writeSocket(y, sizeof(y), print);
  return move;

}

int RemotePlayer::readSocket(GameUI* print) {
    int value;
    ssize_t n = read(socket, &value, sizeof(value));
    if (n == -1) {
        print->socketReadError();
        exit(1);
    }
    return value;
}

void RemotePlayer::writeSocket(int val, size_t valSize, GameUI *print) {
    ssize_t n = write(socket, &val, valSize);
    if (n == -1) {
        print->socketWriteError();
        exit(1);
    }
}