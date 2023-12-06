#pragma once
#define BOARD_W 8
#define BOARD_H 8
#define NUM_PLAYERS 2

#define LEEWAY_MS 200

#ifdef ARDUINO_AVR_UNO
  #define getRandInt(maxVal) random(maxVal)
  #define getTime() millis()
#else
  #define getRandInt(maxVal) (rand() % maxVal)
  #include <chrono>
  #define getTime() std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#endif

enum Direction { LEFT, RIGHT, UP, DOWN };
struct Point {
  int x;
  int y;
};
const Point MOVE_VECS[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

extern unsigned long currT;
