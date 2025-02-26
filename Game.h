#ifdef ARDUINO_AVR_UNO
#include <Arduino.h>
#include "MP3.h"
#include "Note.h"
#else
#include <iostream>
#include <string>
#endif
#include "Board.h"
#include "ScoreDisplay.h"

Player* players;
Time startT = 0;
Time currT;

void loop() {
  currT = getTime() - startT;
#ifdef ARDUINO_AVR_UNO
  for (int i = 0; i < NUM_PLAYERS; ++i) {
    players[i].processInput();
  }
  if (startT != 0) {
    checkNote(players, currT);
  }
#else
  int playerSelect;
  std::cin >> playerSelect;
  if (std::cin.good()) {
    if (playerSelect >= 0 && playerSelect < NUM_PLAYERS) {
      players[playerSelect].processInput();
    }
  } else {
    std::cin.clear();
  }
#endif
  displayMap(currT);
  
  if (startT == 0) {
    static int i = 0;
    i = (i+1) % 4;
    writeDigit(DIGIT_PINS[i], statussegments[i]);
  } else {
    displayScores(players);
  }
}

void setup()
{
  setupBoard();
  setupScoreDisplay();
#ifdef ARDUINO_AVR_UNO
  Serial.begin(9600);
  mp3.begin(9600);
  delay(500);  // wait chip initialization is complete
  mp3_command(CMD_SEL_DEV, DEV_TF);  // select the TF card
  delay(500);

  players = new Player[2] {
    {0, new JoystickInput(A1, A0, A2)},
    {1, new JoystickInput(A4, A3, A5)}
  };
#else
  players = new Player[2] {
    {0, new ConsoleInput()},
    {1, new ConsoleInput()}
  };
  startT = getTime(); // just start immediately since no audio playing on command line
#endif
}
