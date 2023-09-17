#include "sprites.hpp"

auto createPlayer(int X, int Y, Color Col) -> Player* {
    static Player pl = {X,Y,Col};
    Player* res = &pl;
    return res;
}

