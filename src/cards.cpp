#include "cards.hpp"
#include <raylib.h>

Cards::IlusionShakerPart::IlusionShakerPart() {
    std::srand(std::time(nullptr));
}
Cards::IlusionShakerPart::~IlusionShakerPart() {}

void Cards::IlusionShakerPart::incTick() {ticks++;}

int Cards::IlusionShakerPart::getTick() {
    return ticks;
}

void Cards::IlusionShakerPart::update() {
    updateSpawner();
    updateTama();
    incTick();
}

void Cards::IlusionShakerPart::draw() {
    for (auto &i : theSpawners) {
        DrawCircleLines(i.x,i.y,15,GREEN);
    }
    for (auto &j : theTamas) {
        if (isTamaDriftting) DrawCircleLines(j.cx + j.r*std::cos(j.t), j.cy + j.r*std::sin(j.t), 8, SKYBLUE);
        else DrawCircle(j.cx + j.r*std::cos(j.t),j.cy + j.r*std::sin(j.t),8,BLUE);
    }
}

void Cards::IlusionShakerPart::updateSpawner() {
    if (ticks % 50 == 0 && theSpawners.size() < max_spawner_count && isTamaDriftting == false) {
        float offset1 = 1 + std::rand()/((RAND_MAX + 1u)/50);
        float offset2 = 1 + std::rand()/((RAND_MAX + 1u)/50);
        Spawner res1 = {0,300+offset1,true,false};
        Spawner res2 = {800,300+offset2,false,false};
        theSpawners.push_back(res1);
        theSpawners.push_back(res2);
    }

    for (auto &i : theSpawners) {
        if (isTamaDriftting == true) break;
        if (i.isGoingLeft) i.x += spawner_speed;
        else i.x -= spawner_speed;
        if (i.x > 900 || i.x < -100) {i.isDel = true;}
        if (ticks % 13 == 0 && theTamas.size() < max_tama_count) {
            Tama res1 = {i.x, i.y, 0, 0, false, i.isGoingLeft, false};
            Tama res2 = {i.x, i.y, 0, 0, true, i.isGoingLeft, false};
            theTamas.push_back(res1);
            theTamas.push_back(res2);
        }
    }

    std::vector<Spawner>::const_iterator itr_spawner = theSpawners.begin();

    for (itr_spawner; itr_spawner != theSpawners.end(); itr_spawner++) {
        Spawner temp = *itr_spawner;
        if (temp.isDel) {theSpawners.erase(itr_spawner);}
    }

    if (ticks % 200 == 199 && isTamaDriftting == false) isTamaDriftting = true;
    if (isTamaDriftting && tamaDriftTimer < 100) {
        tamaDriftTimer++;
        for (auto &i : theTamas) {
            if (i.parentDirection == true) i.cx -= 1.5;
            else i.cx += 1.5;
        }
    } else {
        isTamaDriftting = false;
        tamaDriftTimer = 0;
    }
}

void Cards::IlusionShakerPart::updateTama() {

    if (isTamaDriftting == true) return;

    for (auto &i : theTamas) {
        if (i.isGoingUp) {
            i.r += tama_speed;
            i.t = DEG2RAD * 90;
        } else {
            i.r -= tama_speed;
            i.t = DEG2RAD * 90;
        }
        if (std::abs(i.r) > 400) {i.isDel = true;}
    }

    std::vector<Tama>::const_iterator itr_tama = theTamas.begin();

    for (itr_tama; itr_tama != theTamas.end(); itr_tama++) {
        Tama temp = *itr_tama;
        if (temp.isDel) {theTamas.erase(itr_tama);}
    }
}
