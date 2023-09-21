#pragma once

#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=2;
        EntityManager* em;
        Animation* killableAnim;

};