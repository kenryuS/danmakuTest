#include "raylib.h"
#include "sprites.hpp"
#include "cards.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

// global vars
Player* player = createPlayer(400, 300, RED);
const float player_speed = 3.0f;
int globalTick = 0;
int hitnum = 0;
int grazenum = 0;
auto spellCard = new Cards::IlusionShakerPart;
// global vars end

// util func
auto getRecCord(float cx, float cy, float r, float t) -> Vector2 {
    float x = r*std::cos(t) + cx;
    float y = r*std::sin(t) + cy;
    return (Vector2){x,y};
}
//util func end

auto update() -> void {
    spellCard->update();
    //if (globalTick % 60 == 0) std::cout << spellCard->getTick() << std::endl;
    if (globalTick % 5 == 0 && !spellCard->isTamaDriftting) {
        for (auto i : spellCard->theTamas) {
            if (CheckCollisionCircles((Vector2){player->x, player->y}, 2, getRecCord(i.cx, i.cy, i.r, i.t), 4)) hitnum++;
            if (CheckCollisionCircles((Vector2){player->x, player->y}, 10, getRecCord(i.cx, i.cy, i.r, i.t), 8)) grazenum++;
        }
    }
    globalTick++;
}

auto keyevents() -> void {
    if (IsKeyDown(KEY_LEFT) && player->x > 0) {player->x -= player_speed;}
    if (IsKeyDown(KEY_RIGHT) && player->x < 800) {player->x += player_speed;}
    if (IsKeyDown(KEY_UP) && player->y > 0) {player->y -= player_speed;}
    if (IsKeyDown(KEY_DOWN) && player->y < 600) {player->y += player_speed;}
}

auto draw() -> void {BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircle(player->x, player->y, 10, player->col);
    DrawCircle(player->x, player->y, 2, BLUE);
    spellCard->draw();
    DrawFPS(20,20);
    std::string hitstat = std::to_string(hitnum);
    std::string grazestat = std::to_string(grazenum);
    DrawText(("Hit: " + hitstat).c_str(), 20, 40, 18, DARKGREEN);
    DrawText(("Graze: " + grazestat).c_str(), 20, 60, 18, DARKGREEN);
EndDrawing();}

auto main(int argc, char** argv) -> int {
    // init
    const int winWidth = 800;
    const int winHeight = 600;
    InitWindow(winWidth, winHeight, "danmakuTest");
    SetTargetFPS(60);
    // init end

    // main loop
    while (!WindowShouldClose()) {
        keyevents();
        update();
        draw();
    }
    // main loop end

    // quit game
    CloseWindow();
    delete(spellCard);
    // quit game end
    return 0;
}
