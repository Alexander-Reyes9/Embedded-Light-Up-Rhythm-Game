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
extern const unsigned long* NOTE_TIMES[];
//extern const unsigned int* NOTE_LENGTHS[];
extern const int NOTE_CT[];

void checkNote(Player* players, unsigned long currT);
void clearNote();

extern uint8_t songNum;