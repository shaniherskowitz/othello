//
// Created by shani herskowitz on 11/20/17.
//

#include <limits>
#include "HumanPlayer.h"
HumanPlayer::HumanPlayer(Tile symbol) : Player(symbol) {

}
HumanPlayer::~HumanPlayer() {

}
Move HumanPlayer::getTurnsMove(vector<Move> movesList, GameUI *print, Board& board) {
  print->printBoard(board);
  if (movesList.empty()) {
    print->movesListIsEmpty();
    return Move(Point(-1, -1));
  }
  print->printMoves(getSymbolMeaning(), movesList);
  Move move = getUserInput(print);
  while (!inMoves(move, movesList)) {
    print->repeatUserInput();
    print->printMoves(getSymbolMeaning(), movesList);
    move = getUserInput(print);
  }
  return move;
}

Move HumanPlayer::getUserInput(GameUI* print) const {
  print->userInput();
  int i, j;
  while (true) {
    cin >> i  >> j;
    if (!cin.fail()) break;
    print->problemWithInput();
    cin.clear();
    cin.ignore(std::numeric_limits<int>::max(),'\n');
  }
  return Move(Point(i - 1, j - 1));
}

bool HumanPlayer::inMoves(Move move, vector<Move> movesList) const {
  vector<Move>::iterator it = movesList.begin();
  while (it != movesList.end()) {
    if (it->getPoint() == move.getPoint()) { return true;}
    it++;
  }
  return false;
}
