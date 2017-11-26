//
// Created by shani herskowitz on 11/18/17.
//
#include "Game.h"

Game::Game(Player *one1, Player *two1, GameUI *print1, int size1) {
  one = one1;
  two = two1;
  size = size1;
  print = print1;
}
Game::~Game() {

}


void Game::run() {
  GameLogic *logic = new RegularGameLogic();
  Board board(size);
  GameUI *print = new ConsolUI();
  Tile player1 = one->getSymbol();
  Tile player2 = two->getSymbol();
  vector<Move> moves1 = logic->getMovesList(player1, board);
  vector<Move> moves2 = logic->getMovesList(player2, board);
  GameStatus gameStatus = GameStatus(IN_PROGRESS);
  bool noMovesFlag;

  while (gameStatus == GameStatus(IN_PROGRESS) || gameStatus == GameStatus(HAS_NO_MOVES) || noMovesFlag) {
    gameStatus = logic->turn(*one, board, print);
    if (gameStatus == GameStatus(HAS_NO_MOVES)) noMovesFlag = true;
    gameStatus = logic->turn(*two, board, print);
    if(moves1.empty() && moves2.empty()) break;
  }
  print->printBoard(board, board.getSize());
  Score *s = new Score(board);
  print->declareWinner(one->getSymbolMeaning(), two->getSymbolMeaning(), *s, player1, player2);

}