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
    } while (board[y][x].player != NULL || board[y][x].note != NULL);
    board[y][x].note = note;
  }
}
void checkNote(Player* players, unsigned long currT) {
  if (currentNote > (sizeof(NOTE_TIMES) / sizeof(NOTE_TIMES[0]))) {
    return;
  }
  if (currT > NOTE_TIMES[currentNote]) {
    spawnNote(players);
    currentNote++;
  }
}
