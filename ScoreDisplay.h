#pragma once
#ifdef ARDUINO_AVR_UNO
const int dataPin = 10;
const int clockPin = 6;
const int latchPin = 9;

const uint8_t DIGIT_PINS[] = {2, 4, 7, 8};

const int SEG_A = 1 << 0;
const int SEG_B = 1 << 1;
const int SEG_C = 1 << 2;
const int SEG_D = 1 << 3;
const int SEG_E = 1 << 4;
const int SEG_F = 1 << 5;
const int SEG_G = 1 << 6;

int digit2segments[10] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_B | SEG_C,
  SEG_A | SEG_B | SEG_G | SEG_E | SEG_D,
  SEG_A | SEG_B | SEG_G | SEG_C | SEG_D,
  SEG_F | SEG_G | SEG_B | SEG_C,
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,
  SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,
  SEG_A | SEG_B | SEG_C,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_F | SEG_G
};

int statussegments[4] = {
  SEG_D,
  digit2segments[5],
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,
  SEG_F | SEG_E | SEG_D
};
#else
#include <iostream>
#endif
#include "Player.h"

void setupScoreDisplay()
{
#ifdef ARDUINO_AVR_UNO
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < 4; ++i) {
    pinMode(DIGIT_PINS[i], OUTPUT);
    digitalWrite(DIGIT_PINS[i], HIGH);
  }
#endif
}

#ifdef ARDUINO_AVR_UNO
void writeDigit(uint8_t digitPin, int bits)
{
  static int previousDigitPin = 13;
  digitalWrite(previousDigitPin, HIGH);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, bits);
  digitalWrite(latchPin, HIGH);
  digitalWrite(digitPin, LOW);
  previousDigitPin = digitPin;
  //delay(1);
  //digitalWrite(digitPin, HIGH);
}
#endif

int i = 0;
void displayScores(Player* players)
{
#ifdef ARDUINO_AVR_UNO
  i = (i + 1) % 4;
  switch(i) {
    case 0:
      writeDigit(DIGIT_PINS[0], digit2segments[players[1].score / 10]);
      break;
    case 1:
      writeDigit(DIGIT_PINS[1], digit2segments[players[1].score % 10]);
      break;
    case 2:
      writeDigit(DIGIT_PINS[2], digit2segments[players[0].score / 10]);
      break;
    case 3:
      writeDigit(DIGIT_PINS[3], digit2segments[players[0].score % 10]);
      break;
  }
#else
  std::cout << "0: " << players[0].score << ", 1: " << players[1].score << std::endl;
#endif
}
