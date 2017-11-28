//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//


#include <gtest/gtest.h>
#include "../Board.h"
TEST (tileAmountTest, TileCount) {

  char path[] = "../boardFiles/board4";
  Board *board = new Board(path);
  EXPECT_EQ(10, board->getXTiles());
  EXPECT_EQ(19, board->getOTiles());

  char path2[] = "../boardFiles/board5";
  Board *board2 = new Board(path2);
  EXPECT_EQ(5, board2->getXTiles());
  EXPECT_EQ(4, board2->getOTiles());

  char path3[] = "../boardFiles/board6";
  Board *board3 = new Board(path3);
  EXPECT_EQ(8, board3->getXTiles());
  EXPECT_EQ(27, board3->getOTiles());

  delete board;
  delete board2;
  delete board3;
}

TEST(charAtTileTest, charTest) {
  char path[] = "../boardFiles/board3";
  Board *board = new Board(path);
  EXPECT_EQ('O', board->getTile(1, 1));
  EXPECT_EQ('X', board->getTile(2, 2));
  EXPECT_EQ('X', board->getTile(5, 4));
  EXPECT_EQ('X', board->getTile(4, 5));

  delete board;

}

TEST (ifFullTest, FullBoard) {
  char path[] = "../boardFiles/fullboard";
  Board *board = new Board(path);
  EXPECT_EQ(true, board->boardFull());

  delete board;
}