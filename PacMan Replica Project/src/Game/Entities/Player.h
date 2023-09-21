#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "PowerUp.h"


enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity{

    private:
        int spawnX, spawnY;
        unsigned int health=3;
        int score=0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;
        bool paused = false;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;

    public:
        Player(int, int, int , int, EntityManager*, string);
        ~Player();
        int getHealth();
        int getScore();
        int getDotCount();
        int counter;
        int strawCounter;
        int tplocation;
        
        bool getPausedState();
        bool powerupped;
        bool strawberried = false;
        bool immortal = false;
        FACING getFacing();
        
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void setPausedState(bool);
        void setSpeed(int);

        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();

        vector<int> AvailableXcoords;
        vector<int> AvailableYcoords;
};