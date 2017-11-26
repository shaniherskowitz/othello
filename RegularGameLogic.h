//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_REGULARGAMELOGIC_H
#define OTHELLO_REGULARGAMELOGIC_H

#include "GameLogic.h"
class RegularGameLogic: public GameLogic {
 public:
  RegularGameLogic();
  GameStatus turn(Player &player, Board &board, GameUI *print);
  vector<Move> getMovesList(Tile player, Board &board);
  vector<Move> findMoves(int i, int j, Tile symbol, Board &board);
  vector<Move> mergeMovesList(vector<Move> movesList, vector<Move> currentMovesList);
  bool inBound(int boardSize, int row, int col) const;
  int getOptionalMove(Board& board, Point point, Tile symbol, int dir1, int dir2, int sum);
  void traverseBoard(Board& gameBoard, Point point, int dir1, int dir2, Tile tile) const;
  void flipTiles(Board& board, Tile tile, Point location) const;
  void updateBoardCounters(Board &board, Tile tile) const;
};

#endif //OTHELLO_REGULARGAMELOGIC_H
