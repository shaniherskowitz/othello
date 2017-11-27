//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_REGULARGAMELOGICTEST_H
#define OTHELLO_REGULARGAMELOGICTEST_H

#include "GameLogic.h"
class RegularGameLogic : public GameLogic {

  vector<Move> findMoves(int i, int j, Tile symbol, Board &board);
  vector<Move> mergeMovesList(vector<Move> movesList, vector<Move> currentMovesList);
  bool inBound(int boardSize, int row, int col) const;
  void traverseBoard(Board &gameBoard, Point point, int dir1, int dir2, Tile tile) const;
  int getOptionalMove(Board &board, Point point, Tile symbol, int dir1, int dir2, int sum);
  void updateBoardCounters(Board &board, Tile tile) const;
 public:
  friend class test_RegularGameLogic;
  RegularGameLogic();
  ~RegularGameLogic();
  GameStatus turn(Player &player, Board &board, GameUI *print);
  vector<Move> getMovesList(Tile player, Board &board);
  void flipTiles(Board &board, Tile tile, Point location) const;
};

#endif //OTHELLO_REGULARGAMELOGICTEST_H
