#pragma once
#include "Player.h"

struct Empty {};

typedef Player* PPlayer;

struct BoardElement {
  enum {Player, Empty} type = Empty;
  union Value {
    PPlayer as_player;
  } value;
};
extern BoardElement board[BOARD_H][BOARD_W];

void setupLEDs();
void displayMap();
