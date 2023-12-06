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
  200, 700, 1200, 1700
};
const unsigned int NOTE_LENGTHS[] = {
  300, 300, 300, 300
};

void checkNote(Player* players);
void clearNote();
