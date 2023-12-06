
#ifndef ARDUINO_AVR_UNO
#include <cstdlib>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
#else
#include <Arduino.h>
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
  board[y][x].type = BoardElement::Player;
  board[y][x].value.as_player = this;
}

bool Player::move(Direction dir, bool checkDelay) {
  if (checkDelay) {
  #ifdef ARDUINO_AVR_UNO
    unsigned long currT = millis();
  #else
    unsigned long long currT = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  #endif
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
  if (board[newY][newX].type != BoardElement::Empty) {
    if (board[newY][newX].type == BoardElement::Player) {
      // if it's a player, we can try and push the player
      if (!board[newY][newX].value.as_player->move(dir, false)) {
        return false;
      }
    }
  }
  board[y][x].type = BoardElement::Empty;
  x = newX;
  y = newY;
  board[y][x].type = BoardElement::Player;
  board[y][x].value.as_player = this;
  return true;
}

void Player::processInput() {
  im->handle(this);
}
