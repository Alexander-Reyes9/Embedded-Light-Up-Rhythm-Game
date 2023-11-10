#include <iostream>
#include "Board.h"
#include <string>
using namespace std;

std::vector<std::vector<BoardElement>> map(BOARD_H, std::vector<BoardElement>(BOARD_W, std::monostate{}));

void initMap() {
  /*for (int i = 0; i < BOARD_H; ++i)
    for (int j = 0; j < BOARD_W; ++j)
      map[i][j]= monostate();*/
}

int main ()
{
  initMap();
  Player players[2] = {0, 1};
  string input = "";
  cin >> input;
  
  while (input != "done")
  {
    int playerSelect = stoi(input);
    cin >> input;
    if (input == "up")
    {
      players[playerSelect].move(Direction::UP);
    }
    else if (input == "down")
    {
      players[playerSelect].move(Direction::DOWN);
    }
    else if (input == "right")
    {
      players[playerSelect].move(Direction::RIGHT);
    }
    else if (input == "left")
    {
      players[playerSelect].move(Direction::LEFT);
    }
    else {
      cout << "invalid input" << endl;
    }
    /*for (int i = 0; i < 2; ++i) {
      cout << "Player " << i << endl;
      cout << '\t' << players[i].x << endl;
      cout << '\t' << players[i].y << endl;
    }*/
    for (int i = 0; i < BOARD_H; ++i) {
      for (int j = 0; j < BOARD_W; ++j) {
        cout << (char)(holds_alternative<monostate>(map[i][j]) ? '-' : (std::get<Player*>(map[i][j])->id + '0'));
      }
      cout << endl;
    }
    cin >> input;
  }
  return 0;
}
