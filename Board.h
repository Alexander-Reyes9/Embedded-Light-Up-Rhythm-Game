#pragma once
#include "Note.h"
#include "Player.h"

struct BoardElement {
  Player* player;
  Note* note;
};
extern BoardElement board[BOARD_H][BOARD_W];

void setupBoard();
void displayMap(unsigned long currT);
