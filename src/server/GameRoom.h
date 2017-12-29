#ifndef OTHELLO_GAMEROOM_H
#define OTHELLO_GAMEROOM_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include "Point.h"
#include <cstdlib>
#include <strings.h>
#define END_GAME -2

using namespace std;

/**
 * Defining a GameRoom class to control communication between players in a game.
 */
class GameRoom {

  bool started;
  int playerSocket1;
  int playerSocket2;
  string name;

    /**
   * The method initializes the player for the game.
   * @param playerSocket The player's socket number.
   * @param playerNum A number to represent the symbol of the player.
   */
    void initializingPlayer(int playerSocket, int playerNum);

public:
    /**
     * The GameRoom constructor
     * @param playerSocket1 The first connecting player's socket.
     * @param name The game name.
     */
  GameRoom(int playerSocket1, const string &name);

    /**
     * The GameRoom destructor.
     */
  ~GameRoom();

    /**
     * The method adds the player to the game.
     * @param playerSocket The player''s socket.
     */
  void connectPlayer2(int playerSocket);

    /**
     * The method returns the name of the GameRoom.
     * @return The game name.
     */
  const string &getName() const;

    /**
     * The method checks if the game was started.
     * @return True if the game was staetwd, else false.
     */
  bool isStarted() const;

    /**
     * The method starts a game with both connected players.
     */
  void startGame();

    /**
     * The method closes the game and connections.
     */
  void closeGame();

    /**
     * The method returns the other player socket.
     * @param playerSocket The current player's socket.
     * @return The other player's socket.
     */
  int getOtherSocket(int playerSocket);

    /**
     * The method checks if the player is playing in theis game.
     * @param playerSocket The given player's socket.
     * @return True if the player is playing in this gameRoom and else false.
     */
  bool playingInGame(int playerSocket);

    /**
     * The method checks the read/write to socket and will print an a message
     * accordingly.
     * @param n The return value from read/write.
     * @param msg The message to print.
     */
  void checkSocketConnection(ssize_t n, string msg);
};

#endif //OTHELLO_GAMEROOM_H
