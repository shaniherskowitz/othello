//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H
#include <iostream>
#include "Tile.h"
#include "Point.h"
#include <fstream>
#define DEF_SIZE 8

using namespace std;

/**
 * Defining a board class.
 */
class Board {
  Tile **board;
  int size;
  int xTiles;
  int oTiles;

 public:

  /**
   * The Board's constructor with a default size of 8.
   * @param size The board's size.
   */
  explicit Board(int size = DEF_SIZE);

  /**
   * The Board's copy constructor.
   * @param board The board to be copied.
   */
  explicit Board(Board *board);

  /**
   * The Board's constructor from file.
   * @param filePath The file's path.
   */
  explicit Board(char filePath[]);

  /**
   * The Board's destructor.
   */
  ~Board();

  /**
   * The method returns th board's size.
   * @return The board's size.
   */
  int getSize() const;

  /**
   * The method returns the actual game board.
   * @return The actual game board.
   */
  Tile **getBoard() const;

/**
 *  The method sets the given Tile at the given location and updates the
 *  board accordingly.
 * @param The give point to update.
 * @param The given tile symbol to update.
 */
  void setTile(Point &point, Tile symbol);

/**
 * The method returns true if the board is full, and else false.
 * @return True if the board is full, and else false.
 */
  bool boardFull() const;

  /**
   * The method returns true if the tile at the given indexes is the opposite
   * tile as the given tile.
   * @param symbol The given tile symbol.
   * @param row The row index.
   * @param col The column index.
   * @return True if the tile at the given indexes is the opposite tile as
   * the given tile.
   */
  bool isOppositeSymbol(Tile symbol, int row, int col);

  /**
   * The method returns true if the tile at the given indexes is the same
   * symbol as the given symbol.
   * @param symbol The given tile symbol.
   * @param row The row index.
   * @param col The column index.
   * @return True if the tile at the given indexes is the same
   * symbol as the given symbol.
   */
  bool isSameSymbol(Tile symbol, int row, int col);

  /**
   * The method updates the xTiles with one and oTiles counter minus one,
   * because an X tile was flipped.
   */
  void flipXTiles();

  /**
   * The method updates the oTiles with one and xTiles counter minus one,
   * because an O tile was flipped.
   */
  void flipOTiles();

  /**
   * The method changes the tile symbol to the opposite symbol at the given indexes.
   * @param row The given row index.
   * @param col The given column index.
   */
  void flipTile(int row, int col);

  /**
   * The method returns the tile symbol at the given indexes.
   * @param row The given row index.
   * @param col The given column index.
   * @return The tile symbol at the given indexes.
   */
  char getTile(int row, int col);

  /**
   * The method returns xTiles.
   * @return The xTiles counter.
   */
  int getXTiles() const;

  /**
   * The method returns oTiles.
   * @return The oTiles counter.
   */
  int getOTiles() const;

  /**
   * The method returns the symbol of player with more tiles on the board,
   * if both players have the same amount of tiles a whitespace will be
   * returned.
   * @return The symbol of the player with more tiles on the board.
   */
  char getWinnerSymbol();

  /**
   * The method returns true if the game is a tie, meaning if xTiles equal
   * oTiles, else false.
   * @return true if the game is a tie, else false.
   */
  bool isTie();

};

#endif //OTHELLO_BOARD_H
