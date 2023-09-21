#pragma once

#include "PowerUp.h"
#include "Player.h"

class SpeedUp : public PowerUp{
    private:
        Player *player;

    public:
        SpeedUp(Player* player);
        void activate();

};