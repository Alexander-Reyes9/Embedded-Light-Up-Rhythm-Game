#pragma once
#include "defs.h"

class Player {
  public:
    Player(int id);
    bool move(Direction dir, bool checkDelay=true);
    int id = 0;
    int x;
    int y;
  private:
    unsigned long lastMoveTime = 0;
    int moveDelayMs = 200;
};
