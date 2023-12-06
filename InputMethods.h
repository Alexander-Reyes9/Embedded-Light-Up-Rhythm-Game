#pragma once
#include "defs.h"

class Player;

class InputMethod {
public:
  virtual void handle(Player* player);
};

#ifdef ARDUINO_AVR_UNO
class JoystickInput : public InputMethod {
public:
  JoystickInput(int pinX, int pinY, int pinButton) : pinX(pinX), pinY(pinY), pinButton(pinButton) { }
  virtual void handle(Player* player) override;
private:
  int pinX;
  int pinY;
  int pinButton;
};
#else
class ConsoleInput : public InputMethod {
public:
  virtual void handle(Player* player) override;
};
#endif
