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

void loop() {
#ifdef ARDUINO_AVR_UNO
  for (int i = 0; i < NUM_PLAYERS; ++i) {
    players[i].processInput();
  }
  checkNote(players);
#else
  int playerSelect;
  std::cin >> playerSelect;
  if (playerSelect >= 0 && playerSelect < NUM_PLAYERS) {
    players[playerSelect].processInput();
  }
#endif
  displayMap();
  displayScores(players);
}
#pragma endregion INPUT

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
  mp3_command(CMD_PLAY, 0x0001);

  players = new Player[2] {
    {0, new JoystickInput(A1, A0, A2)},
    {1, new JoystickInput(A4, A3, A5)}
  };
#else
  players = new Player[2] {
    {0, new ConsoleInput()},
    {1, new ConsoleInput()}
  };
#endif
}
