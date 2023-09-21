#include "StrawberryUp.h"

StrawberryUp::StrawberryUp(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    
    sprite.cropFrom(spriteSheet,504,49,16,16);
    
}