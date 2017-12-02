//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
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
  GameStatus gameStatus = IN_PROGRESS;
  GameStatus player1TurnStatus = GameStatus(NOT_STARTED), player2TurnStatus = GameStatus(NOT_STARTED);

  while (gameStatus == IN_PROGRESS) {
    player1TurnStatus = logic->turn(*player1, board, print);
    if (player1TurnStatus == HAS_NO_MOVES && player2TurnStatus == HAS_NO_MOVES) {
      gameStatus = HAS_NO_MOVES;
      break;
    }
    if (player1TurnStatus == FULL_BOARD) {
      gameStatus = FULL_BOARD;
      break;
    }
    player2TurnStatus = logic->turn(*player2, board, print);
    if (player1TurnStatus == HAS_NO_MOVES && player2TurnStatus == HAS_NO_MOVES) {
      gameStatus = HAS_NO_MOVES;
      break;
    }
    if (player2TurnStatus == FULL_BOARD) {
      gameStatus = FULL_BOARD;
      break;
    }
  }
  print->printBoard(board);
  print->declareWinner(board, gameStatus);

  delete logic;

}