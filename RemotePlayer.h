//
// Created by shani herskowitz on 12/2/17.
//

#ifndef OTHELLO_REMOTEPLAYER_H
#define OTHELLO_REMOTEPLAYER_H

#include "Player.h"
class RemotePlayer : public Player  {
explicit RemotePlayer(Tile tile);
  ~RemotePlayer();
};

#endif //OTHELLO_REMOTEPLAYER_H
