#include "Board.h"

#define NUM_LEDS BOARD_W * BOARD_H

BoardElement board[BOARD_H][BOARD_W] = {{}};

#ifdef ARDUINO_AVR_UNO
#define LEDS_DATA_PIN 3
#include <FastLED.h>
CRGB leds[NUM_LEDS];

void setupLEDs() {
  FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(leds, NUM_LEDS);
}
#else
#include <iostream>
using namespace std;
#endif

void displayMap() {
#ifdef ARDUINO_AVR_UNO
  for (int y = 0; y < BOARD_H; ++y) {
    for (int x = 0; x < BOARD_W; ++x) {
      int ind = y * BOARD_W + x;
      BoardElement elem = board[y][x];
      if (elem.type == BoardElement::Player) {
        leds[ind] = elem.value.as_player->id == 0 ? CRGB::Blue : CRGB::Red;
      }
    }
  }
  FastLED.show();
#else
  for (int i = 0; i < BOARD_H; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      cout << (char)((board[i][j].type == BoardElement::Empty) ? '-' : (board[i][j].value.as_player->id + '0'));
    }
    cout << endl;
  }
#endif
}
