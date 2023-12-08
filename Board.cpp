#include "Board.h"

BoardElement board[BOARD_H][BOARD_W] = {{{}}};

#ifdef ARDUINO_AVR_UNO
#define NUM_LEDS 64
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

void displayMap(Time currT) {
#ifdef ARDUINO_AVR_UNO
  for (int by = 0; by < BOARD_H*2; ++by) {
    for (int bx = 0; bx < BOARD_W*2; ++bx) {
      int ind = by * 8 + ((by % 2 == 0) ? (8 - 1 - bx) : bx); // goes right to left on even index rows
      int y = by / 2;
      int x = bx / 2;
      BoardElement& elem = board[y][x];
      if (elem.note != NULL) {
        Note* note = elem.note;
        auto t = NOTE_TIMES[songNum][note->id];
        auto l = 1000;//NOTE_LENGTHS[songNum][note->id];

        long relativeToEndT = (long)t + l - currT;
        if (relativeToEndT < 0) {
          if (relativeToEndT < -LEEWAY_MS) {
            elem.note = NULL; // note expired
          }
          leds[ind] = CRGB::Black;
          continue;
        }
        const int BRIGHTNESS = 100;
        auto b = BRIGHTNESS - relativeToEndT * BRIGHTNESS / l;
        Player* player = note->owner;
        leds[ind] = player->id == 0 ? CRGB(0, b, BRIGHTNESS - b) : player->id == 1 ? CRGB(BRIGHTNESS - b, b, 0) : CRGB::Purple;
      } else if (elem.player != NULL) {
        Player* player = elem.player;
        leds[ind] = player->id == 0 ? CRGB(0, 0, 10) : player->id == 1 ? CRGB(10, 0, 0) : CRGB::Purple;
      } else {
        leds[ind] = CRGB::Black;
      }
    }
  }
  FastLED.show();
#else
  //system("clear");
  for (int i = 0; i < BOARD_H; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      cout << (char)((board[i][j].player != NULL) ? (board[i][j].player->id + '0') : '-');
    }
    cout << endl;
  }
#endif
}
