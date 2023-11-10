#include <cstdlib>
#include <iostream>
#include <chrono>
#include "Board.h"
using namespace std;
using namespace std::chrono;
bool inBounds(int x, int y) {
  return x >= 0 && y >= 0 && x < BOARD_W && y < BOARD_H;
}
Player::Player(int id) 
{
  x = (rand() % BOARD_W);
  y = (rand() % BOARD_H);
  this->id = id;
  map[y][x] = this;
}

bool Player::move(Direction dir, bool checkDelay) {
  if (checkDelay) {
  #ifdef AVR_UNO
    long long currT = millis();
  #else
    long long currT = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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
  if (!holds_alternative<monostate>(map[newY][newX])) {
    if (holds_alternative<Player*>(map[newY][newX])) {
      // if it's a player, we can try and push the player
      if (!get<Player*>(map[newY][newX])->move(dir)) {
        return false;
      }
    } else {
      return false;
    }
  }
  map[y][x] = monostate{};
  x = newX;
  y = newY;
  map[y][x] = this;
  return true;
}
