#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 

class CharacterState : public State {
	private:
		ofImage img1;
		ofImage img2;
		ofImage img3;

		Button *CharButton1;
		Button *CharButton2;
		Button *CharButton3;

		Animation* anim;
		Animation* anim2;
		Animation* anim3;

		string selectedCharacter = "pacman";

	public:
		CharacterState();
		~CharacterState();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void reset();
		string getCharacter();
};
