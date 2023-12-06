#pragma once
#ifdef ARDUINO_AVR_UNO
const int dataPin = 10;
const int clockPin = 6;
const int latchPin = 9;

const uint8_t digit0Pin = 4;
const uint8_t digit1Pin = 7;
const uint8_t digit2Pin = 8;
const uint8_t digit3Pin = 12;

int digit2segments[10] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111
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

  pinMode(digit0Pin, OUTPUT);
  digitalWrite(digit0Pin, HIGH);
  pinMode(digit1Pin, OUTPUT);
  digitalWrite(digit1Pin, HIGH);
  pinMode(digit2Pin, OUTPUT);
  digitalWrite(digit2Pin, HIGH);
  pinMode(digit3Pin, OUTPUT);
  digitalWrite(digit3Pin, HIGH);
#endif
}

int previousDigitPin = 13;
void writeDigit(uint8_t digitPin, int value)
{
  digitalWrite(previousDigitPin, HIGH);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit2segments[value]);
  digitalWrite(latchPin, HIGH);
  digitalWrite(digitPin, LOW);
  previousDigitPin = digitPin;
  //delay(1);
  //digitalWrite(digitPin, HIGH);
}

int i = 0;
void displayScores(Player* players)
{
#ifdef ARDUINO_AVR_UNO
  i = (i + 1) % 4;
  switch(i) {
    case 0:
      writeDigit(digit0Pin, players[1].score / 10);
      break;
    case 1:
      writeDigit(digit1Pin, players[1].score % 10);
      break;
    case 2:
      writeDigit(digit2Pin, players[0].score / 10);
      break;
    case 3:
      writeDigit(digit3Pin, players[0].score % 10);
      break;
  }
#else
  std::cout << "0: " << players[0].score << "1: " << players[1].score << std::endl;
#endif
}
