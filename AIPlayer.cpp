//
// Created by shani herskowitz on 11/22/17.
//

#include "AIPlayer.h"
#include "RegularGameLogic.h"
AIPlayer::AIPlayer(Tile symbol) : Player(symbol){}

AIPlayer::~AIPlayer() {}

Move AIPlayer::getTurnsMove(vector<Move> movesList, GameUI *print,Board &board) {
  print->printBoard(board, board.getSize());
  if (movesList.empty()) {
    print->movesListIsEmpty();
    return Move(Point(-1, -1));
  }
  print->printMoves(getSymbolMeaning(), movesList);

  int minScore = 1000, check = 0, index = -1;

  for (int i = 0; i < movesList.size(); i++) {
    check = simulateMove(&board, movesList[i]);
    if(minScore > check) {
      minScore = check;
      index = i;
    }
  }
  print->computerMove(movesList[index].getPoint());
  return movesList[index];
}

int AIPlayer::simulateMove(Board *board, Move move) {
  Board *copyBoard = new Board(board);
  GameLogic *logic = new RegularGameLogic();
  int computerScore = 0, humanScore = 0, currentScore = 0;

  logic->flipTiles(*copyBoard, symbol, move.getPoint());

  computerScore = copyBoard->getOTiles();
  humanScore = copyBoard->getXTiles();

  vector<Move> otherPlayerMoves = logic->getMovesList(Tile(X), *copyBoard);

  if (otherPlayerMoves.empty()) return 100;

  for (int i = 0; i < otherPlayerMoves.size(); i++) {
    if (currentScore < otherPlayerMoves[i].getScoreCounter()) {
      currentScore = otherPlayerMoves[i].getScoreCounter();
    }
  }
  currentScore = (currentScore + humanScore + 1) - (computerScore - currentScore);
  delete copyBoard;

  return currentScore;

}