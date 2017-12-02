//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include "AIPlayer.h"
#include "RegularGameLogic.h"
AIPlayer::AIPlayer(Tile symbol) : Player(symbol) {}

AIPlayer::~AIPlayer() {}

Move AIPlayer::getTurnsMove(vector<Move> movesList, GameUI *print, Board &board) {
  print->printBoard(board);
  if (movesList.empty()) {
    print->movesListIsEmpty();
    return Move(Point(NOT_INDEX, NOT_INDEX));
  }
  print->printMoves(getSymbolMeaning(), movesList);

  int minScore = LARGE_NUM, check = 0, index = NOT_INDEX;

  for (int i = 0; i < movesList.size(); i++) {
    check = simulateMove(&board, movesList[i]);
    if (minScore > check) {
      minScore = check;
      index = i;
    }
  }
  //print->computerMove(movesList[index].getPoint());
  return movesList[index];
}

int AIPlayer::simulateMove(Board *board, Move move) {
  Board copyBoard(board);
  GameLogic *logic = new RegularGameLogic();
  int computerScore = 0, humanScore = 0, currentScore = 0;

  logic->flipTiles(copyBoard, symbol, move.getPoint());

  computerScore = copyBoard.getOTiles();
  humanScore = copyBoard.getXTiles();
  vector<Move> otherPlayerMoves = logic->getMovesList(Tile(X), copyBoard);

  if (otherPlayerMoves.empty()) {
    delete logic;
    return 0;
  }
  for (int i = 0; i < otherPlayerMoves.size(); i++) {
    if (currentScore < otherPlayerMoves[i].getScoreCounter()) currentScore = otherPlayerMoves[i].getScoreCounter();
  }
  currentScore = (currentScore + humanScore + TURN_FLIP) - (computerScore - currentScore);
  delete logic;
  return currentScore;
}