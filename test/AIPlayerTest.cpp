//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include "../src/client/AIPlayer.h"
#include "gtest/gtest.h"
#include "AIPlayerTest.h"
#include "../src/client/RegularGameLogic.h"
TEST_F (AIPlayerTest, AITest) {
  GameLogic *logic = new RegularGameLogic();

  Board *board = new Board(8);
  GameUI *print = new ConsolUI();
  vector<Move> moves = logic->getMovesList(player1.getSymbol(), *board);

  EXPECT_EQ(Move(Point(2, 4)).getPoint(), player1.getTurnsMove(moves, print, *board).getPoint());
  delete board;
  delete print;

}
TEST_F (AIPlayerTest, AITest2) {
  GameLogic *logic = new RegularGameLogic();

  char path[] = "../boardFiles/board1";
  Board *board = new Board(path);

  GameUI *print = new ConsolUI();
  vector<Move> moves = logic->getMovesList(player1.getSymbol(), *board);

  EXPECT_NE(Move(Point(2, 4)).getPoint(), player1.getTurnsMove(moves, print, *board).getPoint());
  delete board;
  delete print;

}
TEST_F (AIPlayerTest, AITest3) {
  GameLogic *logic = new RegularGameLogic();

  char path[] = "../boardFiles/board2";
  Board *board = new Board(path);

  GameUI *print = new ConsolUI();
  vector<Move> moves = logic->getMovesList(player1.getSymbol(), *board);

  Point move = Move(Point(7, 5)).getPoint();
  Point player = player1.getTurnsMove(moves, print, *board).getPoint();

  EXPECT_NE(move, player);
  delete board;
  delete print;

}
TEST_F (AIPlayerTest, AITest4) {
  GameLogic *logic = new RegularGameLogic();

  char path[] = "../boardFiles/board4";
  Board *board = new Board(path);

  GameUI *print = new ConsolUI();
  vector<Move> moves = logic->getMovesList(player1.getSymbol(), *board);

  EXPECT_EQ(Move(Point(7, 5)).getPoint(), player1.getTurnsMove(moves, print, *board).getPoint());
  delete board;
  delete print;

}
TEST_F (AIPlayerTest, AITest5) {
  GameLogic *logic = new RegularGameLogic();

  char path[] = "../boardFiles/board5";
  Board *board = new Board(path);

  GameUI *print = new ConsolUI();
  vector<Move> moves = logic->getMovesList(player1.getSymbol(), *board);

  EXPECT_EQ(Move(Point(1, 4)).getPoint(), player1.getTurnsMove(moves, print, *board).getPoint());
  delete board;
  delete print;

}
TEST_F (AIPlayerTest, AITest6) {
  GameLogic *logic = new RegularGameLogic();

  char path[] = "../boardFiles/board6";
  Board *board = new Board(path);

  GameUI *print = new ConsolUI();
  vector<Move> moves = logic->getMovesList(player1.getSymbol(), *board);

  EXPECT_EQ(Move(Point(4, 6)).getPoint(), player1.getTurnsMove(moves, print, *board).getPoint());
  delete board;
  delete print;

}

TEST_F(AIPlayerTest, SymbolTest) {
  EXPECT_EQ('O', player1.getSymbolMeaning());
}
