#include "RegularGameLogic.h"

RegularGameLogic::RegularGameLogic() {}

RegularGameLogic::~RegularGameLogic() {}

GameStatus RegularGameLogic::turn(Player &player, Board &board, GameUI *gameUI) {
  vector<Move> movesList = getMovesList(player.getSymbol(), board);
  Move move = player.getTurnsMove(movesList, gameUI, board);
  if (move.getPoint() == Point(-1, -1)) return HAS_NO_MOVES;
  if (move.getPoint() == Point(-2, -2)) return FULL_BOARD;
  flipTiles(board, player.getSymbol(), move.getPoint());
  gameUI->played(move.getPoint(), player.getSymbolMeaning());
  if (board.boardFull()) return FULL_BOARD;
  return IN_PROGRESS;
}

vector<Move> RegularGameLogic::getMovesList(Tile playerSymbol, Board &board) {
  vector<Move> movesList;
  Tile **gameBoard = board.getBoard();
  for (int i = 0; i < board.getSize(); i++) {
    for (int j = 0; j < board.getSize(); j++) {
      if (gameBoard[i][j] == playerSymbol) {
        vector<Move> currentMovesList = findMoves(i, j, playerSymbol, board);
        movesList = mergeMovesList(movesList, currentMovesList);
      }
    }
  }
  return movesList;
}

vector<Move> RegularGameLogic::findMoves(int row, int col, Tile symbol, Board &board) {
  Point point(row, col);
  vector<Move> movesList;
  for (int dir1 = 1; dir1 >= -1; dir1--) {
    for (int dir2 = 1; dir2 >= -1; dir2--) {
      if (dir1 == 0 && dir2 == 0) continue;
      int counter = getOptionalMove(board, point, symbol, dir1, dir2, 0);
      if (counter > 0) {
        movesList.push_back(Move(Point(row + (counter + 1) * dir1, col + (counter + 1) * dir2), counter));
      }
    }
  }
  return movesList;
}

vector<Move> RegularGameLogic::mergeMovesList(vector<Move> movesList, vector<Move> currentMovesList) {
  vector<Move>::iterator it = currentMovesList.begin();
  bool contains = false;
  while (it != currentMovesList.end()) {
    vector<Move>::iterator it1 = movesList.begin();
    while (it1 != movesList.end()) {
      if (it->getPoint() == it1->getPoint()) {
        it1->mergeMove(*it);
        contains = true;
        break;
      }
      it1++;
    }
    if (!contains) movesList.push_back(*it);
    it++;
  }
  return movesList;
}

bool RegularGameLogic::inBound(int boardSize, int row, int col) const {
  return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
}

int RegularGameLogic::getOptionalMove(Board &board, Point point, Tile symbol, int dir1, int dir2, int sum) {
  int size = board.getSize();
  int row = point.getX();
  int col = point.getY();
  Tile **gameBoard = board.getBoard();

  if (!inBound(size, row, col) || !inBound(size, row + dir1, col + dir2)) return 0;
  if (board.isOppositeSymbol(symbol, row + dir1, col + dir2)) {
    if (!inBound(size, row + 2 * dir1, col + 2 * dir2)) return 0;
    if (board.isSameSymbol(symbol, row + 2 * dir1, col + 2 * dir2)) return 0;
    if (gameBoard[row + 2 * dir1][col + 2 * dir2] == Tile(EMPTY)) return ++sum;
    return getOptionalMove(board, Point(row + dir1, col + dir2), symbol, dir1, dir2, ++sum);
  }
  return 0;
}

void RegularGameLogic::traverseBoard(Board &gameBoard, Point point, int dir1, int dir2, Tile tile) const {
  Tile **board = gameBoard.getBoard();
  int row = point.getX();
  int col = point.getY();
  int size = gameBoard.getSize();

  if (!inBound(size, row, col) || !inBound(size, row + dir1, col + dir2)) return;
  if (board[row + dir1][col + dir2] == Tile(EMPTY)) return;
  if (gameBoard.isSameSymbol(tile, row + dir1, col + dir2)) return;
  if (!inBound(size, row + 2 * dir1, col + 2 * dir2)) return;
  if (gameBoard.isOppositeSymbol(tile, row + dir1, col + dir2) &&
      board[row + 2 * dir1][col + 2 * dir2] == Tile(EMPTY))
    return;
  if (gameBoard.isOppositeSymbol(tile, row + dir1, col + dir2) &&
      gameBoard.isOppositeSymbol(tile, row + 2 * dir1, col + 2 * dir2)) {
    traverseBoard(gameBoard, Point(row + dir1, col + dir2), dir1, dir2, tile);
  }
  if (gameBoard.isOppositeSymbol(tile, row + dir1, col + dir2) &&
      gameBoard.isSameSymbol(tile, row + 2 * dir1, col + 2 * dir2)) {
    gameBoard.flipTile(row + dir1, col + dir2);
    updateBoardCounters(gameBoard, tile);
  }
}

void RegularGameLogic::flipTiles(Board &board, Tile tile, Point location) const {
  if (location == Point(-1, -1)) throw std::out_of_range ("tile location not in range gameLogic/flipTiles");
  board.setTile(location, tile);
  int i, j;
  for (i = 1; i >= -1; i--) {
    for (j = 1; j >= -1; j--) {
      if (i == 0 && j == 0) continue;
      traverseBoard(board, Point(location.getX(), location.getY()), i, j, tile);
    }
  }
}

void RegularGameLogic::updateBoardCounters(Board &board, Tile tile) const {
  if (tile == Tile(X)) board.flipXTiles();
  if (tile == Tile(O)) board.flipOTiles();
}
