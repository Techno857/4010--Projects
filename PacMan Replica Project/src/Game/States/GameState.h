#pragma once

#include "State.h"
#include "Player.h"
#include "MapBuilder.h"

class GameState: public State{
    public: 
        GameState();
		~GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		void setPause(bool Pause);

		void setCharacter(string);

		bool getPause();
		int getFinalScore();
	
	private:
		ofSoundPlayer music;
		ofImage mapImage;
		Map* map;

		string ReceivedSprite;

		int finalScore=0;
		bool Pause = false;

};