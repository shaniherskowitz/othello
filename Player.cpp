//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//

#include "Player.h"
Player::Player(Tile name) {
  this->symbol = name;
}
Player::~Player() {

}

Tile Player::getSymbol() const {
  return symbol;
}

char Player::getSymbolMeaning() const {
  if (symbol == Tile(O)) return 'O';
  else return 'X';
}