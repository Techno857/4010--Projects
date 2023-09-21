#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h"

class PauseState : public State {
	private:
		ofImage img1;
		Button *resumeButton;
		Button *quitButton;
		Animation* anim;
	
	public:
		PauseState();
		~PauseState();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void reset();
};