#include "Board.h"

//Note spawnedNotes[4][NUM_PLAYERS];
int currentNote = 0;
void spawnNote(Player* players) {
  for (int i = 0; i < NUM_PLAYERS; ++i) {
    Note* note = new Note{currentNote, players + i};
    int x, y;
    do {
      x = getRandInt(BOARD_W);
      y = getRandInt(BOARD_H);
    } while (board[y][x].type != BoardElement::Empty);
    board[y][x].type = BoardElement::Note;
    board[y][x].value.as_note = note;
  }
}
void clearNote() {
  for (int y = 0; y < BOARD_H; ++y) {
    for (int x = 0; x < BOARD_W; ++x) {
      //if (board[y][x].type == BoardElement::Note) {
        
      //}
    }
  }
}
void checkNote(Player* players) {
  if (currentNote > (sizeof(NOTE_TIMES) / sizeof(NOTE_TIMES[0]))) {
    return;
  }
  #ifdef ARDUINO_AVR_UNO
    unsigned long currT = millis();
  #else
    unsigned long long currT = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  #endif
  if (currentNote > 0) {
    if (currT > NOTE_TIMES[currentNote - 1] + NOTE_LENGTHS[currentNote - 1]) {
      clearNote();
    }
  }
  if (currT > NOTE_TIMES[currentNote]) {
    spawnNote(players);
    currentNote++;
  }
}
