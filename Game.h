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
  /*Serial.print("x:");
  Serial.print(xIn);
  Serial.print(",y:");
  Serial.print(yIn);
  Serial.print(",l:");
  Serial.println(xIn * xIn + yIn * yIn);*/
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
  /*for (int i = 0; i < 2; ++i) {
    cout << "Player " << i << endl;
    cout << '\t' << players[i].x << endl;
    cout << '\t' << players[i].y << endl;
  }*/
#endif
  displayMap();
}
#pragma endregion INPUT

void setup()
{
  //Serial.begin(9600);
  //delay(1000);
  setupBoard();
  players = new Player[2]{0, 1};
}
