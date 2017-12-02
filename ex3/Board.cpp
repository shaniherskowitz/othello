//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include <cstdlib>
#include "Board.h"
using namespace std;
Board::Board(int size1) {

  this->size = size1;
  this->board = new Tile *[size];

  int i, j;
  for (i = 0; i < size; i++) {
    board[i] = new Tile[size];
    for (j = 0; j < size; j++) {
      board[i][j] = Tile(EMPTY);
    }
  }
  i = size / 2 - 1;
  j = size / 2;
  board[i][i] = Tile(O);
  board[i][j] = Tile(X);
  board[j][i] = Tile(X);
  board[j][j] = Tile(O);
  xTiles = 2;
  oTiles = 2;

}

Board::Board(Board *board) {
  this->size = board->size;
  this->board = new Tile *[size];

  int i;
  for (i = 0; i < size; i++) {
    this->board[i] = new Tile[board->size];
  }
  for (int k = 0; k < size; k++) {
    for (int j = 0; j < size; j++) {
      this->board[k][j] = board->board[k][j];
    }
  }

  xTiles = board->xTiles;
  oTiles = board->oTiles;
}

Board::Board(char filePath[]) {
  size = DEF_SIZE;
  xTiles = 0, oTiles = 0;
  this->board = new Tile *[size];
  for (unsigned int i = 0; i < size; i++) {
    board[i] = new Tile[size];
  }
  ifstream inFile;
  inFile.open(filePath);
  char x;
  if (!inFile) {
    cerr << "Unable to open file";
    exit(1);   // call system to stop
  }
  int k = 0, l = 0;
  while (inFile >> x && l < size && k < size) {

    if (x == 'X') {
      board[k][l] = Tile(X);
      xTiles++;
    } else if (x == 'O') {
      board[k][l] = Tile(O);
      oTiles++;
    }
    if (x == '-') board[k][l] = Tile(EMPTY);
    l++;
    if (l == size) {
      l = 0;
      k++;
    }

  }

  inFile.close();
}

Board::~Board() {
  for (int i = 0; i < size; i++) {
    delete board[i];
  }
  delete[] board;
}

int Board::getSize() const {
  return size;
}

Tile **Board::getBoard() const {
  return board;
}

void Board::setTile(Point &point, Tile symbol) {

  board[point.getX()][point.getY()] = symbol;
  if (symbol == Tile(O)) oTiles++;
  if (symbol == Tile(X)) xTiles++;

}
int Board::getXTiles() const {
  return xTiles;
}
int Board::getOTiles() const {
  return oTiles;
}

bool Board::boardFull() const {
  return (xTiles + oTiles == size * size);
}

bool Board::isOppositeSymbol(Tile symbol, int row, int col) {
  return board[row][col] != symbol && board[row][col] != Tile(EMPTY);
}
bool Board::isSameSymbol(Tile symbol, int row, int col) {
  return board[row][col] == symbol;
}

void Board::flipXTiles() {
  xTiles++;
  oTiles--;
}
void Board::flipOTiles() {
  oTiles++;
  xTiles--;
}

void Board::flipTile(int row, int col) {
  if (board[row][col] == Tile(O)) board[row][col] = Tile(X);
  else if (board[row][col] == Tile(X)) board[row][col] = Tile(O);

}

char Board::getTile(int i, int j) {
  if (board[i][j] == Tile(X)) return 'X';
  if (board[i][j] == Tile(O)) return 'O';
  return ' ';
}

char Board::getWinnerSymbol() {
  if (xTiles > oTiles) return 'X';
  if (xTiles < oTiles) return 'O';
  return ' ';
}

bool Board::isTie() { return xTiles == oTiles; }