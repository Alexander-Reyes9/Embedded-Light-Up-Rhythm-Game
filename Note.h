#pragma once
#include "defs.h"
#include "Player.h"

#ifdef ARDUINO_AVR_UNO
#include <Arduino.h>
#endif

struct Note {
  int id;
  Player* owner;
};

// times in ms of when notes should start
const unsigned long NOTE_TIMES[] = {
  1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 1000
};
const unsigned int NOTE_LENGTHS[] = {
  3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000
};

void checkNote(Player* players, unsigned long currT);
void clearNote();
