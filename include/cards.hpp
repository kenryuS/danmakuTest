#ifndef CARDS
#define CARDS

#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "sprites.hpp"

namespace Cards {

class IlusionShakerPart {
    public:
        IlusionShakerPart();
        ~IlusionShakerPart();

        void updateSpawner();
        void updateTama();
        void update();

        void incTick();
        int getTick();

        std::vector<Tama> theTamas;
        std::vector<Spawner> theSpawners;
        bool isTamaDriftting = false;

        void draw();

    private:
        const int max_spawner_count = 20;
        const int max_tama_count = max_spawner_count * 75;
        const float spawner_speed = 2.0f;
        const float tama_speed = 2.0f;
        int ticks = 0;
        int tamaDriftTimer = 0;
};

}

#endif // CARDS
