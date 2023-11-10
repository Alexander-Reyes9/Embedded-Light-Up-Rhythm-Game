#pragma once
#include "defs.h"
class Player {
  public:
    Player(int id);
    bool move(Direction dir, bool checkDelay=true);
    int id = -1;
  private:
    int x;
    int y;
    int lastMoveTime = 0;
    int moveDelayMs = 100;
};
