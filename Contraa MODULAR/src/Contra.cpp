/*
 * Contra.cpp
 *
 *  Created on: 8 sep. 2018
 *      Author: lucio
 */
#include "Contra.h"
#include <stdio.h>
#include <string>
#include "Timer.h"
#include "LTexture.h"
#include "Player.h"


Contra::Contra() {

	// TODO Auto-generated constructor stub

}

Contra::~Contra() {
	// TODO Auto-generated destructor stub
}


bool Contra::init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Contra - Parallax",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Contra::loadMedia() {
	//Loading success flag
	bool success = true;
	gSpriteClips[ WALKING_ANIMATION_FRAMES ];


	//Load player texture
	if( !gPlayerTexture.loadFromFile( "images/Player1.png" )) {
		printf( "Failed to load player texture!\n" );
		success = false;
	}
	else
    {
        //Set sprite clips

        //Idle animation

		gSpriteClips[0].x = 143;
        gSpriteClips[0].y = 17;
        gSpriteClips[0].w = 23;
        gSpriteClips[0].h = 34;

        //Walking animation

        gSpriteClips[1].x = 146;
        gSpriteClips[1].y = 134;
        gSpriteClips[1].w = 23;
        gSpriteClips[1].h = 34;

        gSpriteClips[2].x = 169;
        gSpriteClips[2].y = 134;
        gSpriteClips[2].w = 20;
        gSpriteClips[2].h = 34;

        gSpriteClips[3].x = 192;
        gSpriteClips[3].y = 134;
        gSpriteClips[3].w = 20;
        gSpriteClips[3].h = 34;

        gSpriteClips[4].x = 215;
        gSpriteClips[4].y = 134;
        gSpriteClips[4].w = 23;
        gSpriteClips[4].h = 34;

        gSpriteClips[5].x = 238;
        gSpriteClips[5].y = 43;
        gSpriteClips[5].w = 23;
        gSpriteClips[5].h = 34;

	}

	//Load first background texture
	if( !gBGTexture.loadFromFile( "images/bg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void Contra::close() {
	//Free loaded images
	gPlayerTexture.free();
	gBGTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int Contra::getScreen_height() {
	return this->SCREEN_HEIGHT;
}

int Contra::getScreen_width() {
	return this->SCREEN_WIDTH;
}

int Contra::getLevel_height() {
	return this->LEVEL_HEIGHT;
}

int Contra::getLevel_width() {
	return this->LEVEL_WIDTH;
}

void Contra::clear_screen() {
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
}

void Contra::run() {
	//Main loop flag
	bool quit = false;
	Timer fps;

	//Event handler
	SDL_Event e;

	//The player that will be moving around on the screen
	Player player = Player(LEVEL_HEIGHT, LEVEL_WIDTH);

	//The camera area
	SDL_Rect camera = { 0, 0, 800, 600 };
	//While application is running
	while( !quit ) {
		//Start the frame timer
		fps.start();

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
				quit = true;
			}

			//Handle input for the player
			player.handleEvent( e );
		}

		//Move the player
		player.move();


		//Center the camera over the player
		camera.x = ( player.getPosX() + Player::PLAYER_WIDTH / 2 ) -
				SCREEN_WIDTH / 2;
		camera.y = SCREEN_HEIGHT / 2;


		//Keep the camera in bounds
		if( camera.x < 0 ) {
			camera.x = 0;
		}
		if( camera.y < 0 ){
			camera.y = 0;
		}
		if( camera.x > LEVEL_WIDTH - camera.w ){
			camera.x = LEVEL_WIDTH - camera.w;
		}
		if( camera.y > LEVEL_HEIGHT - camera.h ){
			camera.y = LEVEL_HEIGHT - camera.h;
		}

		//Clear screen
		//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		//SDL_RenderClear( gRenderer );
		clear_screen();

		//Render background
		gBGTexture.render( 0, 0, &camera);

		//Render objects
		player.renderPlayer( camera.x, camera.y, gSpriteClips, frame, gPlayerTexture);

		//Update screen
		SDL_RenderPresent( gRenderer );

		//Go to next frame
		++frame;

		//Cycle animation
		if( frame / WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES ) {
			frame = 0;
		}

		if((frame / 5 >= 3 ) && (debug_mode)){
			 printf("PosX: %d\nPosY: %d\n\n",player.getPosX(),player.getPosY());
		}

		//If we want to cap the frame rate
		if ( fps.get_ticks() < 1000 / SCREEN_FPS ) {
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / SCREEN_FPS ) - fps.get_ticks() );
		}
	//Free resources and close SDL
	}
	close();
}



