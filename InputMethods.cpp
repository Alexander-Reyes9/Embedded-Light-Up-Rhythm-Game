#include "InputMethods.h"
#include "Player.h"

#ifdef ARDUINO_AVR_UNO
#include <Arduino.h>

#define THRESHOLD 256
void JoystickInput::handle(Player* player) {
  long xIn = (512 - analogRead(pinX));
  long yIn = (512 - analogRead(pinY));
  
  if ((xIn * xIn + yIn * yIn) > ((long)THRESHOLD * THRESHOLD)) {
    if (abs(xIn) > abs(yIn)) {
      player->move(xIn < 0 ? LEFT : RIGHT);
    } else {
      player->move(yIn < 0 ? DOWN : UP);
    }
  }
  
  if (!digitalRead(pinButton)) {
    player->activate();
  }
}
#else
#include <iostream>
class ConsoleInput : InputMethod {
public:
  virtual override void handle(Player* player) {
    char input;
    cin >> input;
    if (input == 'u')
    {
      player->move(Direction::UP);
    }
    else if (input == 'd')
    {
      player->move(Direction::DOWN);
    }
    else if (input == 'r')
    {
      player->move(Direction::RIGHT);
    }
    else if (input == 'l')
    {
      player->move(Direction::LEFT);
    }
    else if (input == 'x') {
      player->activate();
    }
    else {
      cout << "invalid input" << endl;
    }
  }
}
#endif
