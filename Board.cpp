#include "Board.h"
#include <FastLED.h>

#define NUM_LEDS BOARD_W * BOARD_H

using namespace std;
vector<vector<BoardElement>> map(BOARD_H, vector<BoardElement>(BOARD_W, monostate{}));
CRGB leds[NUM_LEDS];

void setupLEDs() {
  FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(leds, NUM_LEDS);
}

void displayMap() {
#ifdef AVR_UNO
  for (int y = 0; y < BOARD_H; ++y) {
    for (int x = 0; x < BOARD_W; ++x) {
      int ind = y * BOARD_W + x;
      BoardElement elem = map[y][x];
      if (holds_alternative<Player*>(elem)) {
        leds[ind] = get<Player*>(elem)->color;
      }
    }
  }
  FastLED.show();
#elif
  for (int i = 0; i < BOARD_H; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      cout << (char)(holds_alternative<monostate>(map[i][j]) ? '-' : (get<Player*>(map[i][j])->id + '0'));
    }
    cout << endl;
  }
#endif
}
