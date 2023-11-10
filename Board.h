#pragma once
#include <variant>
#include <vector>
#include "Player.h"
typedef std::variant<Player*, std::monostate> BoardElement;
extern std::vector<std::vector<BoardElement>> map;
