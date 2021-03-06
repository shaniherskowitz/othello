#ifndef OTHELLO_HUMANPLAYER_H
#define OTHELLO_HUMANPLAYER_H

#include "Player.h"
#define NOT_INDEX -1
#include <limits>

/**
 * Defining a HumanPlayer class which implements the player interface.
 */
class HumanPlayer : public Player {
 protected:
  /**
  * The method gets the move from the user.
  * @param gameUI The game gameUI.
  * @return The player's chosen move.
  */
  virtual Move getUserInput(GameUI *gameUI) const;

  /**
* The method checks if the given moves is an optional move.
* @param move The given move.
* @param moves The list of optional moves.
* @return True if the move is in the moves list and else false.
*/
  bool inMoves(Move move, vector<Move> moves) const;

 public:
  /**
   * The HumnPlayer constructor.
   * @param symbol Te players symbol.
   */
  explicit HumanPlayer(Tile symbol);

  /**
   * The HumanPlayer's destructor.
   */
  ~HumanPlayer();

  /**
   * THe method gets the players chosen move.
   * @param movesList The players optional moves.
   * @param print The gameUI
   * @param board Te games board.
   * @return The chosen move.
   */
  virtual Move getTurnsMove(vector<Move> movesList, GameUI *print, Board &board);

};

#endif //OTHELLO_HUMANPLAYER_H
