//
// Created by shani herskowitz on 11/20/17.
//

#include "ConsolUI.h"
#include "Player.h"
ConsolUI::ConsolUI() {

}
ConsolUI::~ConsolUI() {

}

void ConsolUI::printMoves(char symbol, vector<Move> &movesList) const {
  cout << symbol << ": It's your move" << endl;
  cout << "your possible moves: ";
  if (!movesList.empty()) {
    vector<Move>::iterator it = movesList.begin();
    while (it != movesList.end()) {
      Point p = Point(it->getPoint().getX() +  1, it ->getPoint().getY() + 1);
      p.print();
      it++;
    }
    cout << endl;
  }
}
void ConsolUI::movesListIsEmpty() const {
  cout << "No possible moves. Play passes back to the other player. Press any key to continue (followed by enter)" << endl;
}

void ConsolUI::printBoard(Board &board, int size) const {
  cout << " | ";
  int i;
  for (i = 1; i <= size; i++) {
    cout << i << " | ";
  }
  cout << endl;
  for (i = 0; i < size; i++) {
    int j;
    for (j = 0; j < 4 * (size + 1); j++) {
      cout << "-";
    }
    cout << endl;
    cout << i + 1 << "| ";
    for (j = 0; j < size; j++) {
      cout << board.getTile(i, j) << " | ";
    }
    cout << endl;
  }
}

void ConsolUI::declareWinner(char player1, char player2, Score const &score, Tile one, Tile two) const {
  Point *p = score.checkScore(one, two);

  cout << "GAME OVER!";

  if (p->getX() > p->getY()) {
    cout << endl << "Player " << player1 << " is the winner!!";
  } else if (p->getY() > p->getX()) {
    cout << endl << "Player " << player2 << " is the winner!!";
  } else {
    cout << endl << "Its a tie!!!";
  }
  cout << endl << "Final Score: Player "
       << player1 << ": " << p->getX() << " Player " << player2 << ": " << p->getY();

  delete p;

}

void ConsolUI::problemWithInput() const {
  cout <<  "Value entered not compatible! Please enter again:" << endl;
}

void ConsolUI::repeatUserInput() const {
  cout <<  "Cant make move! Please enter one of your possible moves - row col:" << endl;
}

void ConsolUI::userInput() const {
  cout << "Please enter your move - row col:" << endl;
}

void ConsolUI::showMenu() const {
  cout << "Please select opponent:" << endl;
  cout << "Option 1 - Human Player" << endl;
  cout << "Option 2 - Computer Player" << endl;


}

void ConsolUI::gameStart(int choice) const{
  cout << endl;
  cout << "You have selected to play vs ";
  if (choice == 1) cout << "Human Player!" << endl;
  else if(choice == 2) cout << "Computer Player!" << endl;

  cout << "Your game will begin now!" << endl << endl;
}

void ConsolUI::computerMove(Point p) const {
  cout << "computer has chosen move: " << p.getX() + 1 << " " << p.getY() + 1 << endl;
}