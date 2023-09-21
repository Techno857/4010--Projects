#pragma once

#include "State.h"
#include "MapBuilder.h"
#include "Button.h"
#include "Animation.h" 

class WinState : public State{
    public:
        WinState();
        ~WinState();
        int getFinalScore();
        void tick();
	    void render();
	    void keyPressed(int key);
	    void mousePressed(int x, int y, int button);
        void reset();
    private:
	    ofImage img1;
	    Button *startButton;
	    Animation* anim;
};