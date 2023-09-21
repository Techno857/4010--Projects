#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "SpeedUp.h"
#include "CherryUp.h"
#include "RandomUp.h"
#include "StrawberryUp.h"



Player::Player(int x, int y, int width, int height, EntityManager* em, string ReceivedSprite) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;

    if (ReceivedSprite == "pacman"){
        sprite.load("images/pacman.png");
    }
    if (ReceivedSprite == "redpacman"){
        sprite.load("images/elrojo.png");
    }
    if (ReceivedSprite == "pirahna plant"){
        sprite.load("images/pirahnaplant.png");
    }

    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);
     

    this->em = em;

    moving = MLEFT;
    
}
void Player::tick(){

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }

    if (powerupped){
        counter--;
    }
    if (counter == 0){
        setSpeed(4);
        powerupped = false;
    }

    if (strawberried){
        strawCounter--;
    }
    if (strawCounter == 0){
        immortal = false;
        strawberried = false;
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    if (!strawberried){
        if(facing == UP)
            walkUp->getCurrentFrame().draw(x, y, width, height);
        else if(facing == DOWN)
            walkDown->getCurrentFrame().draw(x, y, width, height);
        else if(facing == LEFT)
            walkLeft->getCurrentFrame().draw(x, y, width, height);
        else if(facing == RIGHT)
            walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case 'm':
            if (health < 3) health++;
            break;
        case ' ':
            SpeedUp speedup = SpeedUp(this);
            speedup.activate();
            powerupped = true;
            counter = ofGetFrameRate()*7;
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
int Player::getDotCount(){ return em->entities.size(); }
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }
void Player::setSpeed(int h){ speed = h; }


void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                AvailableXcoords.push_back(entity->getxCoord());
                AvailableYcoords.push_back(entity->getyCoord());
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                AvailableXcoords.push_back(entity->getxCoord());
                AvailableYcoords.push_back(entity->getyCoord());
                entity->remove = true;
                score += 20;
                em->setKillable(true);
            }
            if(dynamic_cast<CherryUp*>(entity)){
                entity->remove = true;
                tplocation = ofRandom(AvailableXcoords.size());
                x = AvailableXcoords[tplocation];
                y = AvailableYcoords[tplocation];
                AvailableXcoords.push_back(entity->getxCoord());
                AvailableYcoords.push_back(entity->getyCoord());
            }
            if(dynamic_cast<StrawberryUp*>(entity)){
                AvailableXcoords.push_back(entity->getxCoord());
                AvailableYcoords.push_back(entity->getyCoord());
                entity->remove = true;
                immortal = true;
                strawberried = true;
                strawCounter = ofGetFrameRate()*2;
            }
            if(dynamic_cast<RandomUp*>(entity)){
                AvailableXcoords.push_back(entity->getxCoord());
                AvailableYcoords.push_back(entity->getyCoord());
                entity->remove = true;
                score += ofRandom(5000);
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable())
                ghost->remove = true;
            else if(!immortal){
                die();
            }
        }
    }
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}