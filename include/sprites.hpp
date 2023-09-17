#ifndef SPRITES
#define SPRITES

#include "raylib.h"
#include <cmath>

typedef struct Player {
    int x;
    int y;
    Color col;
} Player;

typedef struct Tama {
    float cx;
    float cy;
    float r;
    float t;
    bool isGoingUp;
    bool parentDirection;
    bool isDel;
} Tama;

typedef struct Spawner {
    float x;
    float y;
    bool isGoingLeft;
    bool isDel;
} Spawner;

auto createPlayer(int x, int y, Color col) -> Player*;

#endif // SPRITES
