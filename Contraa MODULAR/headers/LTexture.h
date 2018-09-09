/*
 * LTexture.h
 *
 *  Created on: 8 sep. 2018
 *      Author: lucio
 */

#ifndef HEADERS_LTEXTURE_H_
#define HEADERS_LTEXTURE_H_

#include <SDL2/SDL.h>
#include <string.h>
#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

//Texture wrapper class
class LTexture {
	public:
		//Initializes variables
		LTexture();

		LTexture(SDL_Renderer* gRenderer );

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(string path);

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText(string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

        SDL_Texture* mTexture;
	private:
		//The actual hardware texture

		//Image dimensions
		int mWidth;
		int mHeight;

		SDL_Renderer* gRenderer;
};

#endif /* HEADERS_LTEXTURE_H_ */
