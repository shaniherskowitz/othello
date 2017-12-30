#ifndef OTHELLO_REGULARGAMELOGICTEST_H
#define OTHELLO_REGULARGAMELOGICTEST_H

#include "GameLogic.h"
#include <stdexcept>

class RegularGameLogic : public GameLogic {

  /**
   * The method finds the the possible moves given a position in the board.
   * @param i The position's row index.
   * @param j The position's column index.
   * @param symbol The tile's symbol.
   * @param board The game board.
   * @return
   */
  vector<Move> findMoves(int i, int j, Tile symbol, Board &board);

  /**
   * The method merges two movesLists, by removing the same points.
   * @param movesList The original moves list to be merged to.
   * @param currentMovesList The moves List that will be merged.
   * @return The merged movesList.
   */
  vector<Move> mergeMovesList(vector<Move> movesList, vector<Move> currentMovesList);

  /**
   * The method checks a point if it's bound of the board.
   * @param boardSize The board size.
   * @param row The point's row index.
   * @param col The point's column index.
   * @return
   */
  bool inBound(int boardSize, int row, int col) const;

  /**
   * The method traverse the board from a given point to the given direction.
   * @param gameBoard The game board.
   * @param point The point to start the traversal from.
   * @param dir1 The vertical direction of traversal.
   * @param dir2 The horizontal direction of traversal.
   * @param tile The symbol of the given point on the board.
   */
  void traverseBoard(Board &gameBoard, Point point, int dir1, int dir2, Tile tile) const;

  /**
   * The method traverses the board and returns the amount of tiles that will
   * be flipped traversing given directions of the point assuming it is
   * picked as the move for the turn.
   * @param board The game board.
   * @param point The point to start the traversal from.
   * @param symbol The symbol of the given point on the board.
   * @param dir1 The vertical direction of traversal.
   * @param dir2 The horizontal direction of traversal.
   * @param sum The number of tiles that will flip in the specific direction.
   * @return The number of tiles that will flip in the specific direction.
   */
  int getOptionalMove(Board &board, Point point, Tile symbol, int dir1, int dir2, int sum);

  /**
   * The method updates the board's xTiles and yTiles.
   * @param board THe game board.
   * @param tile The tile symbol.
   */
  void updateBoardCounters(Board &board, Tile tile) const;

 public:

  /**
   * The RegularGameLogic's constructor.
   */
  RegularGameLogic();

  /**
   * The RegularGameLogic's destructor.
   */
  ~RegularGameLogic();

  virtual GameStatus turn(Player &player, Board &board, GameUI *print);
  virtual vector<Move> getMovesList(Tile player, Board &board);
  virtual void flipTiles(Board &board, Tile tile, Point location) const;
};

#endif //OTHELLO_REGULARGAMELOGICTEST_H
