#include "PowerUp.h"
#include "SpeedUp.h"

SpeedUp::SpeedUp(Player *player){
    this->player = player;
}

void SpeedUp::activate(){

    player->setSpeed(6);
    

}