#include "PauseState.h"

PauseState::PauseState() {
	resumeButton = new Button(ofGetWidth()/2-32, ofGetHeight()/3, 64, 50, "Resume");
	quitButton = new Button(ofGetWidth()/2-32, ofGetHeight()/2, 64, 50, "Quit");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);
}

void PauseState::tick() {
	resumeButton->tick();
	quitButton->tick();
	anim->tick();

	if(resumeButton->wasPressed()){
		setNextState("Game");
	}
	if(quitButton->wasPressed()){
		ofExit();
	}

}
void PauseState::render() {
	string title = "Paused";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	resumeButton->render();
	quitButton->render();
}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
	resumeButton->mousePressed(x, y);
	quitButton->mousePressed(x, y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	resumeButton->reset();
	quitButton->reset();
}

PauseState::~PauseState(){
	delete resumeButton;
	delete quitButton;
	delete anim;
}