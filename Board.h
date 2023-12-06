#pragma once
#include "Note.h"
#include "Player.h"

struct Empty {};

typedef Player* PPlayer;
typedef Note* PNote;

struct BoardElement {
  enum {Player, Note, Empty} type = Empty;
  union Value {
    PPlayer as_player;
    PNote as_note;
  } value;
};
extern BoardElement board[BOARD_H][BOARD_W];

void setupBoard();
void displayMap();
