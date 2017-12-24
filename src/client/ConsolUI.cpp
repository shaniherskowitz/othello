#include <algorithm>
#include "ConsolUI.h"

ConsolUI::ConsolUI() {}

ConsolUI::~ConsolUI() {}

void ConsolUI::printMoves(char symbol, vector<Move> &movesList) const {
  cout << symbol << ": It's your move" << endl;
  cout << "Your possible moves: ";
  if (!movesList.empty()) {
    std::sort(movesList.begin(), movesList.end());
    vector<Move>::iterator it = movesList.begin();
    while (it != movesList.end()) {
      Point p = Point(it->getPoint().getX() + 1, it->getPoint().getY() + 1);
      cout << p;
      it++;
    }
    cout << endl;
  }
}
void ConsolUI::movesListIsEmpty() const {
  cout << "No possible moves. Play passes back to the other player." << endl;
}

void ConsolUI::printBoard(Board &board) const {
  int size = board.getSize();
  cout << endl << " | ";
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

void ConsolUI::declareWinner(Board &board, GameStatus gameStatus) const {
  if (gameStatus == HAS_NO_MOVES) {
    cout << "GAME OVER" << endl << "NO MOVES LEFT FOR BOTH PLAYERS..." << endl;
    return;
  }
  if (board.isTie()) {
    cout << "It's a tie!!!" << endl;
    return;
  }
  cout << "Player " << board.getWinnerSymbol() << " is the winner!!!";
  //cout << "Your score is: " << board.getXTiles();// not sure is needed bc score will be only full board.

}

void ConsolUI::problemWithInput() const {
  cout << "Value entered not compatible! Please enter again:" << endl;
}

void ConsolUI::repeatUserInput() const {
  cout << "Cant make move! Please enter one of your possible moves - row col" << endl;
}

void ConsolUI::userInput() const {
  cout << "Please enter your move - row col:" << endl;
}

void ConsolUI::showMenu() const {
  cout << "Please select opponent:" << endl;
  cout << "Option 1 - Human Player" << endl;
  cout << "Option 2 - Computer Player" << endl;
  cout << "Option 3 - Remote Player" << endl;

}

void ConsolUI::gameStart(int choice) const {
  cout << endl;
  cout << "You have selected to play vs ";
  if (choice == 1) cout << "Human Player!" << endl;
  else if (choice == 2) cout << "Computer Player!" << endl;
  else if (choice == 3) cout << "Remote Player!" << endl;

  cout << "Your game will begin now!" << endl << endl;
}

void ConsolUI::computerMove(Point p) const {
  cout << "Computer has chosen move: " << p.getX() + 1 << "," << p.getY() + 1 << endl;
}

void ConsolUI::played(Point p, char player) const {
  cout << player << " played: (" << p.getX() + 1 << "," << p.getY() + 1 << ")" << endl;
}

void ConsolUI::playerConnected(char tile) const {
  cout << "Player " << tile << " connected." << endl;
}
void ConsolUI::playerDisconnected() const {
  cout << "Player disconnected" << endl;
}
void ConsolUI::serverConnected() const {
  cout << "Connected to server" << endl;
}
void ConsolUI::serverConnectError(const char *msg) const {
  cout << "Failed to connect to server. Reason:" << msg << endl;
}
void ConsolUI::socketReadError() const {
  cout << "Error reading move from player." << endl;
}
void ConsolUI::socketWriteError() const {
  cout << "Error writing to socket" << endl;
}
void ConsolUI::waitingForPlayer() const {
  cout << "Waiting for other player to connect..." << endl;
}
void ConsolUI::waitingForPlayerMove() const {
  cout << "Waiting for other player's move..." << endl;
}

void ConsolUI::remotePlayerMenu() const {
  cout << "Please select an option:" << endl;
  cout << "Option 1 - Start new game" << endl;
  cout << "Option 2 - Join game" << endl;
}
void ConsolUI::printGameRoom(string game) const {
  cout << game << endl;
}

void ConsolUI::noAvailableGames() const {
  cout << "No avialable games!" << endl;
}

void ConsolUI::getGames() const {
  cout << "Please select game room:" << endl;
}