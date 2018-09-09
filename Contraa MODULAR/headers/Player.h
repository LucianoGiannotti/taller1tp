/*
 * Player.h
 *
 *  Created on: 8 sep. 2018
 *      Author: lucio
 */

#ifndef HEADERS_PLAYER_H_
#define HEADERS_PLAYER_H_

#include <SDL2/SDL.h>
#include "LTexture.h"
#include <vector>

//The Player that will move around on the screen
class Player {
    public:
		//The dimensions of the Player
		static const int PLAYER_WIDTH = 23;
		static const int PLAYER_HEIGHT = 34;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 8;
		static const int PLAYER_ACC = 2;

		//Initializes the variables
		Player();

		Player(int level_height, int level_width);

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void move();

		//Shows the player on the screen relative to the camera
		void renderPlayer( int camX, int camY, vector<SDL_Rect> gSpriteClips,
				int frame, LTexture gPlayerTexture );

		//Position accessors
		int getPosX();
		int getPosY();

    private:
		//The X and Y offsets of the player
		int mPosX, mPosY;

		//The velocity of the player
		int mVelX, mVelY;

		//Max level height and width
		int LEVEL_WIDTH, LEVEL_HEIGHT;
};

#endif /* HEADERS_PLAYER_H_ */
