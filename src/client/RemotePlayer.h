#ifndef OTHELLO_REMOTEPLAYER_H
#define OTHELLO_REMOTEPLAYER_H

#include "HumanPlayer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define NOT_INDEX -1
/**
 * Defining a RemotePlayer class to play the game remotely.
 */
class RemotePlayer : public HumanPlayer {
  int socket;
  bool localTurn;

  /**
   * The method writes the player's move to the socket.
   * @param print The game UI.
   * @param movesList The possible moves.
   * @return The written move.
   */
  Move writeMove(GameUI *print, vector<Move> movesList);
  /**
   * The method reads the move from the socket.
   * @param print The game UI.
   * @return The read move.
   */
  Move readMove(GameUI *print);

  /**
   *
   * @param move to write
   * @param print print to user
   */
  void writeMove(Move move, GameUI *print);

 public:
  /**
   * The RemotePlayer's constructor.
   * @param tile The Player's symbol.
   * @param socket The player's socket number.
   * @param localTurn1 A boolean value to know if it is the local player's
   * turn, or the remote player's turn.
   */
  RemotePlayer(Tile tile, int socket, bool localTurn1);

  /**
   * The RemotePlayer's constructor.
   * @param tile The Player's symbol.
   * @param localTurn1 A boolean value to know if it is the local player's
   * turn, or the remote player's turn.
   */
  RemotePlayer(Tile tile, bool localTurn1);

  /**
   * The RemotePlayer's destructor.
   */
  ~RemotePlayer();

  /**
   * The method returns the player's move.
   * @param movesList The possible moves list.
   * @param print The game UI.
   * @param board The gam board.
   * @return The player's move.
   */
  Move getTurnsMove(std::vector<Move> movesList, GameUI *print, Board &board);

  /**
   * The method gets the user's move.
   * @param print The gameUI.
   * @return The player's move.
   */
  virtual Move getUserInput(GameUI *print) const;

};

#endif //OTHELLO_REMOTEPLAYER_H
