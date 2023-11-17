#pragma once
#include "defs.h"
#include <FastLED.h>
class Player {
  public:
    Player(int id, CRGB color);
    bool move(Direction dir, bool checkDelay=true);
    int id = -1;
    CRGB color;
  private:
    int x;
    int y;
    int lastMoveTime = 0;
    int moveDelayMs = 100;
};
