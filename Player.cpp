
#ifndef ARDUINO_AVR_UNO
#include <iostream>
#else
#include <Arduino.h>
#include "MP3.h"
#endif
#include "Board.h"

bool inBounds(int x, int y) {
  return x >= 0 && y >= 0 && x < BOARD_W && y < BOARD_H;
}
Player::Player(char id, InputMethod* im)
{
  x = getRandInt(BOARD_W);
  y = getRandInt(BOARD_H);
  this->id = id;
  this->im = im;
  board[y][x].player = this;
}

bool Player::move(Direction dir, bool checkDelay) {
  if (checkDelay) {
    Time currT = getTime();
    if (currT < lastMoveTime + moveDelayMs) {
      return false;
    }
    lastMoveTime = currT;
  }
  Point vec = MOVE_VECS[dir];
  int newX = x + vec.x;
  int newY = y + vec.y;
  if (!inBounds(newX, newY)) {
    return false;
  }
  if (board[newY][newX].player != NULL) {
    // if it's a player, we can try and push the player
    if (!board[newY][newX].player->move(dir, false)) {
      return false;
    }
  }
  board[y][x].player = NULL;
  x = newX;
  y = newY;
  board[y][x].player = this;
  return true;
}

void Player::activate() {
  if (startT == 0) {
    startT = getTime();
    songNum = x;
    mp3_command(CMD_PLAY, songNum);
    return;
  }
  Note*& note = board[y][x].note;
  if (note != NULL) {
    auto t = NOTE_TIMES[songNum][note->id];
    auto l = 1000;//NOTE_LENGTHS[songNum][note->id];
    if (currT > (t + l - LEEWAY_MS) && currT < (t + l + LEEWAY_MS)) {
      score++; 
    }
    note = NULL;
  } else {
    // wall/barrier placing code if we wanna do that
  }
}

void Player::processInput() {
  im->handle(this);
}
