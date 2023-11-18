#ifndef ARDUINO_AVR_UNO
#include <iostream>
#include <string>
#endif
#include "Board.h"
using namespace std;

int main ()
{
  Player players[2] = {0, 1};
#ifdef ARDUINO_AVR_UNO
  setupLEDs();
#else
  string input = "";
  cin >> input;  

  while (input != "done")
  {
    int playerSelect = stoi(input);
    cin >> input;
    if (input == "up")
    {
      players[playerSelect].move(Direction::UP);
    }
    else if (input == "down")
    {
      players[playerSelect].move(Direction::DOWN);
    }
    else if (input == "right")
    {
      players[playerSelect].move(Direction::RIGHT);
    }
    else if (input == "left")
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
    displayMap();
    cin >> input;
  }
#endif
  return 0;
}
