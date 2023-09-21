#include "RandomUp.h"

RandomUp::RandomUp(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    int randomizador = ofRandom(100);
    if (randomizador <= 33){
        sprite.cropFrom(spriteSheet,552,48,16,16); //melon
    }
    else if(randomizador > 33 && randomizador <= 66 ){
        sprite.cropFrom(spriteSheet,536,48,16,16); //apple
    }
    else{
        sprite.cropFrom(spriteSheet,520,48,16,16); //china
    }
}
