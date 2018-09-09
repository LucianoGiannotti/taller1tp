/*
 * Contra.h
 *
 *  Created on: 8 sep. 2018
 *      Author: lucio
 */

#ifndef CONTRA_H_
#define CONTRA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <vector>

class Contra {
public:
	Contra();
	virtual ~Contra();

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	int getScreen_width();

	int getScreen_height();

	int getLevel_width();

	int getLevel_height();

	void clear_screen();

	void run();

private:
	//Debug mode

	bool debug_mode = true;

	//Frames per second
	const int SCREEN_FPS = 30;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

	//The dimensions of the level
	const int LEVEL_WIDTH = 3318;
	const int LEVEL_HEIGHT = 600;

	//Screen dimension constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//Current animation frame

	int frame = 0;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Scene textures
	LTexture gPlayerTexture = LTexture(gRenderer);
	LTexture gBGTexture = LTexture(gRenderer);

	//Walking animation
	const int WALKING_ANIMATION_FRAMES = 4;
	vector<SDL_Rect> gSpriteClips;
	//LTexture gSpriteSheetTexture;
};

#endif /* CONTRA_H_ */
