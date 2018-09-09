/*
 * Player.cpp
 *
 *  Created on: 8 sep. 2018
 *      Author: lucio
 */
#include "Player.h"


Player::Player(int level_height, int level_width) {
	this->LEVEL_HEIGHT = level_height;
	this->LEVEL_WIDTH = level_width;
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= PLAYER_VEL; break;
            case SDLK_DOWN: mVelY += PLAYER_VEL; break;
            case SDLK_LEFT: mVelX -= PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX += PLAYER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PLAYER_VEL; break;
            case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
            case SDLK_LEFT: mVelX += PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX -= PLAYER_VEL; break;
        }
    }
}

void Player::move()
{
    //Move the player left or right
    mPosX += mVelX;

    //If the player went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PLAYER_WIDTH > LEVEL_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the player up or down
    mPosY += mVelY;

    //If the player went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PLAYER_HEIGHT > LEVEL_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Player::renderPlayer( int camX, int camY, vector<SDL_Rect> gSpriteClips,int frame,
		LTexture gPlayerTexture  ) {
    SDL_Rect* currentClip = &gSpriteClips[ frame / 5 ];

    //Show the player relative to the camera
	gPlayerTexture.render( mPosX - camX, mPosY - camY, currentClip );
}

int Player::getPosX()
{
	return mPosX;
}

int Player::getPosY()
{
	return mPosY;
}


