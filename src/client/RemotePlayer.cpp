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
  print->waitingForPlayerMove();
  Point value;
  ssize_t n = read(socket, &value, sizeof(value));
  if (n == -1) {
    print->socketReadError();
    exit(1);
  }
  if (value.getX() == -1) print->movesListIsEmpty();

  return Move(Point(value.getX(), value.getY()));
}

Move RemotePlayer::writeMove(GameUI *print, vector<Move> movesList) {
  if (movesList.empty()) {
    print->movesListIsEmpty();
    Move move = Move(Point(-1, -1));
    writeMove(move, print);
    return move;
  }
  print->printMoves(getSymbolMeaning(), movesList);
  Move move = getUserInput(print);
  while (!inMoves(move, movesList)) {
    print->repeatUserInput();
    print->printMoves(getSymbolMeaning(), movesList);
    move = getUserInput(print);
  }
  writeMove(move, print);
  return move;

}

void RemotePlayer::writeMove(const Move move, GameUI *print) {
  int x = move.getPoint().getX();
  int y = move.getPoint().getY();
  Point p(x, y);
  string play = "play";
  string command = play + " " + p.toString();
  ssize_t n = write(socket, &command, sizeof(command));
  if (n == -1) {
    print->socketWriteError();
    exit(1);
  }
}
