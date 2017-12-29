#include <limits>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include "RemotePlayer.h"
#include <signal.h>

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
  if (n == -1 || n == 0) {
    print->displayMsg("Server is disconnecting");
    return Move(Point(-2, -2));
    //exit(1);
  }
  if (value.getX() == -1) print->movesListIsEmpty();
  if (value.getX() == -2) print->displayMsg("Server is disconnecting");

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
  string command;
  Point p(x, y);
  string play = "play";
  command = play + " " + p.toString();

  int sendSize = (int) command.size();
  try {
    signal(SIGPIPE, SIG_IGN);
    ssize_t n = write(socket, &sendSize, sizeof(int));
    if (n == -1 || n == 0) {
      print->displayMsg("Server is disconnecting");
      return;
    }
    for (int i = 0; i < sendSize; i++) {
      char c = command[i];
      n = write(socket, &c, sizeof(char));
      if (n == -1) {
        print->displayMsg("Server is disconnecting");
        return;
      }
    }
  } catch (exception &e) { print->displayMsg("Server is disconnecting"); }
}

Move RemotePlayer::getUserInput(GameUI *print) const {
  print->displayMsg("Please enter your move - row col:");
  int i, j;
  while (true) {
    cin >> i;
    cin >> j;
    if (!cin.fail()) break;
    print->problemWithInput();
    cin.clear();
    cin.ignore(std::numeric_limits<int>::max(), '\n');
  }
  return Move(Point(i - 1, j - 1));
}

void RemotePlayer::sendCommand(string command, GameUI *print) const {
  int sendSize = (int) command.size();
  ssize_t n = write(socket, &sendSize, sizeof(int));
  if (n == -1) {
    print->displayMsg("Server is disconnecting");
    //exit(1);
  }
  for (int i = 0; i < sendSize; i++) {
    char c = command[i];
    n = write(socket, &c, sizeof(char));
    if (n == -1) {
      print->socketWriteError();
      exit(1);
    }
  }
}

