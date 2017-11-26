//
// Created by shani herskowitz on 11/18/17.
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H
#include <iostream>
#include "Tile.h"
#include "Point.h"
#include <fstream>

using namespace std;

class Board {
  Tile **board;
  int size;
  int xTiles;
  int oTiles;

 public:
/**
 *
 * @param size1 for row and col.
 * @param player1 in the game.
 * @param player2 in the game.
 * initializes the board to begining state.
 */
  explicit Board(int size1 = 8);

  explicit Board (Board *board);

  explicit Board(char filePath[]);

  ~Board();
/**
   * @return size of row and col.
   */
  int getSize() const;
/**
   * @return the array of the board.
   */
  Tile **getBoard() const;
/**
 *
 * @param point to update.
 * @param symbol to update too.
 */
  void setTile(Point &point, Tile symbol);
/**
   * @return if board is filled.
   */
  bool boardFull() const;

  bool isOppositeSymbol(Tile symbol, int row, int col);

  bool isSameSymbol(Tile symbol, int row, int col);

  void flipXTiles();

  void flipOTiles();

  void flipTile(int row, int col);

  char getTile(int i, int j);

  int getXTiles() const;
  int getOTiles() const;
    char getWinnerSymbol();
    bool isTie();

};

#endif //OTHELLO_BOARD_H
