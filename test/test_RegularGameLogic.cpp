//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//
#include "test_RegularGameLogic.h"
#include "../server/AIPlayer.h"

TEST(GetMovesListTest, PlayerHasMoves_Test) {

  RegularGameLogic regularGameLogic = RegularGameLogic();

  Board board = Board();
  const Move arrO[] = {Move(Point(5, 3), 1), Move(Point(3, 5), 1), Move(Point(4, 2), 1), Move(Point(2, 4), 1)};
  vector<Move> movesListO(arrO, arrO + sizeof(arrO) / sizeof(arrO[0]));
  const Move arrX[] = {Move(Point(5, 4), 1), Move(Point(3, 2), 1), Move(Point(4, 5), 1), Move(Point(2, 3), 1)};
  vector<Move> movesListX(arrX, arrX + sizeof(arrX) / sizeof(arrX[0]));
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(O), board), movesListO);
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(X), board), movesListX);

  char path1[] = "../boardFiles/board1";
  Board board1(path1);
  const Move arrO1[] = {Move(Point(4, 2), 1), Move(Point(2, 4), 1), Move(Point(2, 2), 1)};
  vector<Move> movesListO1(arrO1, arrO1 + sizeof(arrO1) / sizeof(arrO1[0]));
  const Move arrX1[] = {Move(Point(5, 5), 1), Move(Point(5, 4), 1), Move(Point(4, 5), 1)};
  vector<Move> movesListX1(arrX1, arrX1 + sizeof(arrX1) / sizeof(arrX1[0]));
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(O), board1), movesListO1);
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(X), board1), movesListX1);

  char path2[] = "../boardFiles/board2";
  Board board2(path2);
  const Move arrO2[] = {Move(Point(6, 4), 1), Move(Point(2, 4), 2), Move(Point(6, 2), 1)};
  vector<Move> movesListO2(arrO2, arrO2 + sizeof(arrO2) / sizeof(arrO2[0]));
  const Move arrX2[] = {Move(Point(5, 5), 1), Move(Point(5, 1), 1), Move(Point(5, 4), 1),
                        Move(Point(4, 5), 1), Move(Point(4, 1), 1), Move(Point(3, 5), 1),
                        Move(Point(3, 1), 1)};
  vector<Move> movesListX2(arrX2, arrX2 + sizeof(arrX2) / sizeof(arrX2[0]));
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(O), board2), movesListO2);
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(X), board2), movesListX2);

}
TEST(GetMovesListTest, FullBoard_Test) {

  RegularGameLogic regularGameLogic = RegularGameLogic();
  char path[] = "../boardFiles/fullboard";
  Board board(path);
  vector<Move> movesList;
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(O), board), movesList);
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(X), board), movesList);
}

TEST(GetMovesListTest, EmptyMovesList_Test) {

  RegularGameLogic regularGameLogic = RegularGameLogic();
  char path[] = "../boardFiles/nomoves";
  Board board(path);
  vector<Move> movesList;
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(O), board), movesList);
  EXPECT_EQ(regularGameLogic.getMovesList(Tile(X), board), movesList);
}

TEST(TurnTest, InProgress_Test) {

  RegularGameLogic regularGameLogic = RegularGameLogic();
  ConsolUI print;
  char path2[] = "../boardFiles/board2";
  Board board2(path2);
  Board board;

  Player* player = new AIPlayer(Tile(O));
  regularGameLogic.flipTiles(board2, Tile(O), Point(5,3));
  regularGameLogic.flipTiles(board, Tile(O), Point(2,4));
  EXPECT_EQ(regularGameLogic.turn(*player, board2, &print), IN_PROGRESS);
  EXPECT_EQ(regularGameLogic.turn(*player, board, &print), IN_PROGRESS);

  delete(player);
}

TEST(TurnTest, FullBoardTest) {

  RegularGameLogic regularGameLogic = RegularGameLogic();
  ConsolUI print;
  char path[] = "../boardFiles/almostfullboard";
  Board board(path);
  Player* player = new AIPlayer(Tile(O));
  EXPECT_EQ(regularGameLogic.turn(*player, board, &print), FULL_BOARD);
  EXPECT_EQ(regularGameLogic.turn(*player, board, &print), HAS_NO_MOVES);

  delete(player);
}

TEST(TurnTest, HasNoMovesTest) {

  RegularGameLogic regularGameLogic = RegularGameLogic();
  ConsolUI print;
  char path[] = "../boardFiles/nomoves";
  Board board(path);
  Player* player = new AIPlayer(Tile(O));
  EXPECT_EQ(regularGameLogic.turn(*player, board, &print), HAS_NO_MOVES);

  delete(player);
}

TEST(FlipTilesTest, TileIsLegal) {
  RegularGameLogic regularGameLogic = RegularGameLogic();
  ConsolUI print;
  char path[] = "../boardFiles/board1";
  Board board(path);
  Player* player = new AIPlayer(Tile(O));
  regularGameLogic.flipTiles(board, Tile(O), Point(2, 2));
  EXPECT_EQ(board.getXTiles(), 3);
  EXPECT_EQ(board.getOTiles(), 3);

  delete(player);
}

TEST(FlipTilesTest, TileNotLegal) {
  RegularGameLogic regularGameLogic = RegularGameLogic();
  ConsolUI print;
  char path[] = "../boardFiles/board1";
  Board board(path);
  Player* player = new AIPlayer(Tile(O));
  EXPECT_THROW(regularGameLogic.flipTiles(board, Tile(O), Point(-1, -1)), std::out_of_range);

  delete(player);
}