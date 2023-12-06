#pragma once
#include "defs.h"
#include "InputMethods.h"

class Player {
  public:
    Player(char id, InputMethod* im);
    bool move(Direction dir, bool checkDelay=true);
    void activate();
    void processInput();
    char id = 0;
    int x;
    int y;
    
    int score = 0;
    int combo = 0;
  private:
    InputMethod* im;
    unsigned long lastMoveTime = 0;
    int moveDelayMs = 200;
};
