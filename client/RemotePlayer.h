//
// Created by shani herskowitz on 12/2/17.
//

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
   * The method reads a move parameter from the socket.
   * @param print The game UI.
   * @return The xVal or yVal of the move.
   */
  int readSocket(GameUI *print);
  /**
   * THe method writes the chosen xVal or yVal of the move to the socket.
   * @param val The value of the number to be written to the socket.
   * @param valSize THe size of val.
   * @param print The game UI.
   */
  void writeSocket(int val, size_t valSize, GameUI *print);

  void writeMoveHelper(Move move, GameUI *print);
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

};

#endif //OTHELLO_REMOTEPLAYER_H
