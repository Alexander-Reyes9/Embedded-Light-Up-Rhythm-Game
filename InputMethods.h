#pragma once
#include "defs.h"

class Player;

class InputMethod {
public:
  virtual void handle(Player* player)=0;
  virtual ~InputMethod() { };
};

#ifdef ARDUINO_AVR_UNO
class JoystickInput : public InputMethod {
public:
  JoystickInput(int pinX, int pinY, int pinButton, int xMult=1, int yMult=1) : pinX(pinX), pinY(pinY), pinButton(pinButton), xMult(xMult), yMult(yMult) { }
  virtual void handle(Player* player) override;
private:
  int pinX;
  int pinY;
  int pinButton;
  int xMult;
  int yMult;
};
#else
class ConsoleInput : public InputMethod {
public:
  virtual void handle(Player* player) override;
};
#endif
