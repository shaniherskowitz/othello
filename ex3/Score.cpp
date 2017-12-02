//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include "Score.h"

Score::Score(Board &board1) {
  board = board1;
}

Score::~Score() {

}

Point *Score::checkScore(Tile player1, Tile player2) const {
  int count1 = 0;
  int count2 = 0;

  for (int i = 0; i < board.getSize(); ++i) {
    for (int j = 0; j < board.getSize(); ++j) {
      if (board.getBoard()[i][j] == player1) {
        count1++;
      }

      if (board.getBoard()[i][j] == player2) {
        count2++;
      }
    }
  }
  return new Point(count1, count2);
}