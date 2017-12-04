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
  if (movesList.empty()) {
    print->movesListIsEmpty();
    return Move(Point(NOT_INDEX, NOT_INDEX));
  }
  print->printMoves(getSymbolMeaning(), movesList);
  if (localTurn) return writeMove(print, movesList);
  else return readMove();

}

Move RemotePlayer::readMove() {
  ssize_t n;
  int x, y;
  n = read(socket, &x, sizeof(int));
  if (n == -1) {
    cout << "Error reading from socket" << endl;
    exit(1);
  }
  n = read(socket, &y, sizeof(int));
  if (n == -1) {
    cout << "Error reading from socket" << endl;
    exit(1);
  }

  return Move(Point(x, y));
}

Move RemotePlayer::writeMove(GameUI* print, vector<Move> movesList) {
  Move move = getUserInput(print);
  while (!inMoves(move, movesList)) {
    print->repeatUserInput();
    print->printMoves(getSymbolMeaning(), movesList);
    move = getUserInput(print);
  }
  ssize_t n;
  int x = move.getPoint().getX(), y = move.getPoint().getY();
  n = write(socket, &x, sizeof(int));
    if (n == -1) {
    cout << "Error writing from socket" << endl;
    exit(1);
  }
  n = write(socket, &y, sizeof(int));
  if (n == -1) {
    cout << "Error writing from socket" << endl;
    exit(1);
  }
  return move;

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

/*Move RemotePlayer::parseMove(string s) {
    int counter = 0;
    char num[10];
    for (int i = 0; i < s.length(); i++) {
        if(s[i] == ' ') continue;
        num[counter] = s[i];
        counter++;
    }
    //int x = stoi(num[0], 1);
}*/

/* sendMovesList(movesList);
    if (movesList.empty()) {
        //print no moves
        return Move(Point());
    }
   int w = write(socket, &movesList, sizeof(movesList));
    if (w == -1) throw "Error writing moves list to socket";
    string move;
    int r = read(socket, &move, sizeof(move));
    if (r == -1) throw "Error reading move from socket";*/

