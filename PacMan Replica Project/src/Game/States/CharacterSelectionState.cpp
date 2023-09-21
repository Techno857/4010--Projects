#include "CharacterSelectionState.h"

CharacterState::CharacterState() {
	CharButton1 = new Button(ofGetWidth()/2-200, ofGetHeight()/2-120, 64, 50, "Pacman Red");
	CharButton2 = new Button(ofGetWidth()/2-50, ofGetHeight()/2-120, 64, 50, "Pacman");
	CharButton3 = new Button(ofGetWidth()/2+100, ofGetHeight()/2-120, 64, 50, "Pirahna Plant");

	img1.load("images/elrojo.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }

	img2.load("images/pacman.png");
	vector<ofImage> rightAnimframes2;
    ofImage temp2;
	for(int i=0; i<3; i++){
        temp2.cropFrom(img2, i*16, 0, 16, 16);
        rightAnimframes2.push_back(temp2);
    }

	img3.load("images/pirahnaplant.png");
	vector<ofImage> rightAnimframes3;
    ofImage temp3;
	for(int i=0; i<3; i++){
        temp3.cropFrom(img3, i*16, 0, 16, 16);
        rightAnimframes3.push_back(temp3);
    }
	anim = new Animation(10,rightAnimframes);
	anim2 = new Animation(10,rightAnimframes2);
	anim3 = new Animation(10,rightAnimframes3);

}
void CharacterState::tick() {
	CharButton1->tick();
	CharButton2->tick();
	CharButton3->tick();
	anim->tick();
	anim2->tick();
	anim3->tick();
	if(CharButton1->wasPressed()){
		selectedCharacter = "redpacman";
		setNextState("Game");
		setFinished(true);
	}
	if(CharButton2->wasPressed()){
		selectedCharacter = "pacman";
		setNextState("Game");
		setFinished(true);
	}
	if(CharButton3->wasPressed()){
		selectedCharacter = "pirahna plant";
		setNextState("Game");
		setFinished(true);
	}
}
void CharacterState::render() {
	string title = "Choose your character:";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-325, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-200, ofGetHeight()/2-100, 100, 100);
	anim2->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	anim3->getCurrentFrame().draw(ofGetWidth()/2+100, ofGetHeight()/2-100, 100, 100);
	CharButton1->render();
	CharButton2->render();
	CharButton3->render();

}

void CharacterState::keyPressed(int key){
	
}

void CharacterState::mousePressed(int x, int y, int button){
	CharButton1->mousePressed(x, y);
	CharButton2->mousePressed(x, y);
	CharButton3->mousePressed(x, y);
}

void CharacterState::reset(){
	setFinished(false);
	setNextState("");
	CharButton1->reset();
	CharButton2->reset();
	CharButton3->reset();
	
}

CharacterState::~CharacterState(){
	delete CharButton1;
	delete CharButton2;
	delete CharButton3;
	delete anim;
	delete anim2;
	delete anim3;
}

string CharacterState::getCharacter(){ return selectedCharacter; }
