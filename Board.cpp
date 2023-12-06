#include "Board.h"

BoardElement board[BOARD_H][BOARD_W] = {{}};

#ifdef ARDUINO_AVR_UNO
#define NUM_LEDS BOARD_W * BOARD_H
#define LEDS_DATA_PIN 3
#include <Arduino.h>
#include <FastLED.h>
CRGB leds[NUM_LEDS];
#else
#include <iostream>
#include <stdlib.h>
using namespace std;
#endif

void setupBoard() {
#ifdef ARDUINO_AVR_UNO
  FastLED.addLeds<WS2812, LEDS_DATA_PIN, GRB>(leds, NUM_LEDS);
#endif
}

void displayMap() {
#ifdef ARDUINO_AVR_UNO
  for (int y = 0; y < BOARD_H; ++y) {
    for (int x = 0; x < BOARD_W; ++x) {
      int ind = y * BOARD_W + ((y % 2 == 0) ? (BOARD_W - 1 - x) : x); // goes right to left on even index rows
      BoardElement elem = board[y][x];
      if (elem.type == BoardElement::Player) {
        Player* player = elem.value.as_player;
        leds[ind] = player->id == 0 ? CRGB(0, 0, 10) : player->id == 1 ? CRGB(10, 0, 0) : CRGB::Purple;
      } else if (elem.type == BoardElement::Note) {
        Note* note = elem.value.as_note;
        Player* player = note->owner;
        leds[ind] = player->id == 0 ? CRGB(0, 0, 10) : player->id == 1 ? CRGB(10, 0, 0) : CRGB::Purple;
      } else {
        leds[ind] = CRGB::Black;
      }
    }
  }
  FastLED.show();
#else
  system("clear");
  for (int i = 0; i < BOARD_H; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      cout << (char)((board[i][j].type == BoardElement::Empty) ? '-' : (board[i][j].value.as_player->id + '0'));
    }
    cout << endl;
  }
#endif
}
