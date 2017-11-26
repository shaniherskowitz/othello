//
// Created by shani herskowitz on 11/18/17.
//
#include "Game.h"

Game::Game(Player *one1, Player *two1, GameUI *print1, int size1) {
  player1 = one1;
  player2 = two1;
  size = size1;
  print = print1;
}
Game::~Game() {
  delete player1;
  delete player2;
  delete print;

}


void Game::run() {
  GameLogic *logic = new RegularGameLogic();
  Board board(size);
  GameUI *print = new ConsolUI();
  Tile tile1 = player1->getSymbol();
  Tile tile2 = player2->getSymbol();
  vector<Move> moves1 = logic->getMovesList(tile1, board);
  vector<Move> moves2 = logic->getMovesList(tile2, board);
  GameStatus gameStatus = GameStatus(IN_PROGRESS);
  bool noMovesFlag = false;

  while (gameStatus == GameStatus(IN_PROGRESS) || gameStatus == GameStatus(HAS_NO_MOVES) || noMovesFlag) {
    gameStatus = logic->turn(*player1, board, print);
    if (gameStatus == GameStatus(HAS_NO_MOVES)) noMovesFlag = true;
    gameStatus = logic->turn(*player2, board, print);
    if(moves1.empty() && moves2.empty()) break;
  }
  print->printBoard(board, board.getSize());
  Score *s = new Score(board);
  print->declareWinner(player1->getSymbolMeaning(), player2->getSymbolMeaning(), *s, tile1, tile2);

  delete print;
  delete s;

}