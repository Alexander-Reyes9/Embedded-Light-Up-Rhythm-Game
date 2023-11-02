#include <cstdlib>
#include <iostream>
#include <chrono>
#include "defs.h"
using namespace std;
using namespace std::chrono;
class Player
{

public: 
    int x;
    int y;
    int lastMoveTime = 0;
    int moveDelayMs = 100;
    int id = -1;


Player(int id) 
{
    x = (rand() % BOARD_W);
    y = (rand() % BOARD_H);
    this->id = id;
    map[y][x] = id;
}

void move(Direction dir) {
    #ifdef AVR_UNO
        long long currT = millis();
    #else
        long long currT = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
        ).count();
    #endif
    if (currT < lastMoveTime + moveDelayMs) {
        return;
    }
    lastMoveTime = currT;
    Point vec = MOVE_VECS[dir];
    int newX = x + vec.x;
    int newY = y + vec.y;
    inBounds(newX, newY);
    if (map[newY][newX] != -1) {

        map[y][x] = -1;
        x = newX;
        y = newY;
        map[y][x] = id;
    }
}
};