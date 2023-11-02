#pragma once
#define BOARD_W 8
#define BOARD_H 8

enum Direction { LEFT, RIGHT, UP, DOWN };
struct Point {
    int x;
    int y;
};
Point MOVE_VECS[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int map [BOARD_H][BOARD_W];