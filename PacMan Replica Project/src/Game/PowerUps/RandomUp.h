#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "PowerUp.h"

class RandomUp : public Entity{
    public:
        RandomUp(int, int, int, int, ofImage);
        int randomizador;
};