#ifdef ARDUINO_AVR_UNO
#include <Arduino.h>
#else
#include <iostream>
#include <string>
#endif
#include "Board.h"
using namespace std;

Player* players;

#pragma region INPUT // TODO: move Input methods to a different file?
#define THRESHOLD 256
void loop() {
#ifdef ARDUINO_AVR_UNO
  long yIn = (512 - analogRead(A0));
  long xIn = (512 - analogRead(A1));
  
  if ((xIn * xIn + yIn * yIn) > ((long)THRESHOLD * THRESHOLD)) {
    if (abs(xIn) > abs(yIn)) {
      players[0].move(xIn < 0 ? LEFT : RIGHT);
    } else {
      players[0].move(yIn < 0 ? DOWN : UP);
    }
  }
#else
  int playerSelect;
  char input;
  cin >> playerSelect >> input;
  if (input == 'u')
  {
    players[playerSelect].move(Direction::UP);
  }
  else if (input == 'd')
  {
    players[playerSelect].move(Direction::DOWN);
  }
  else if (input == 'r')
  {
    players[playerSelect].move(Direction::RIGHT);
  }
  else if (input == 'l')
  {
    players[playerSelect].move(Direction::LEFT);
  }
  else {
    cout << "invalid input" << endl;
  }
#endif
  displayMap();
}
#pragma endregion INPUT

void setup()
{
  setupBoard();
  players = new Player[2]{0, 1};
}
