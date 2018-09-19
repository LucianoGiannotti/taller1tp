//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>

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

//The timer
class Timer
{
    private:
        int startTicks = 0;
        int pausedTicks = 0;
        bool paused = false;
        bool started = false;

    public:
        void start() {
            started = true;
            paused = false;
            startTicks = SDL_GetTicks();
        }

        void stop() {
            started = false;
            paused = false;
        }

        void pause() {
            if (started && !paused) {
                paused = true;
                pausedTicks = SDL_GetTicks() - startTicks;
            }
        }

        void unpause() {
            if (paused) {
                paused = false;
                startTicks = SDL_GetTicks() - pausedTicks;
                pausedTicks = 0;
            }
        }

        int get_ticks() {
            if (started) {
                if (paused) {
                    return pausedTicks;
                } else {
                    return SDL_GetTicks() - startTicks;
                }
            }
            return 0;
        }

        bool is_started() { return started; }
        bool is_paused() { return paused; }
};

//Texture wrapper class
class LTexture
{
    private:
		int mWidth = 0;
		int mHeight = 0;
        SDL_Texture* mTexture = NULL;

		//Deallocates texture
		void free() {
            if(mTexture) {
                SDL_DestroyTexture(mTexture);
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
            }
        }

	public:
		~LTexture() { free(); }

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		void setColor( Uint8 red, Uint8 green, Uint8 blue ) {
            SDL_SetTextureColorMod( mTexture, red, green, blue );
        }

		void setBlendMode( SDL_BlendMode blending ) {
            SDL_SetTextureBlendMode( mTexture, blending );
        }

		//Set alpha modulation
		void setAlpha( Uint8 alpha ) {
	        SDL_SetTextureAlphaMod( mTexture, alpha );
        }

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth() { return mWidth; }
		int getHeight() { return mHeight; }
};

//The Player that will move around on the screen
class Player
{
    private:
		//The X and Y offsets of the player
		int mPosX = 0;
        int mPosY = 0;

		//The velocity of the player
		int mVelX = 0;
        int mVelY = 0;

    public:
		//The dimensions of the Player
		static const int PLAYER_WIDTH = 23;
		static const int PLAYER_HEIGHT = 34;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 8;
		static const int PLAYER_ACC = 2;

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void move();

		//Shows the player on the screen relative to the camera
		void render( int camX, int camY );

		//Position accessors
		int getPosX() { return mPosX; }
		int getPosY() { return mPosY; }
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gPlayerTexture;
LTexture gBGTexture;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( !loadedSurface ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} else {
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0x00, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( !newTexture ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		} else {
			//Get image dimensions
	        mTexture = newTexture;
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	return (newTexture != NULL);
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
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
    if( ( mPosX >= 0 ) && ( mPosX + PLAYER_WIDTH <= LEVEL_WIDTH ) ) {
        mPosX += mVelX;
    }

    if( ( mPosY >= 0 ) && ( mPosY + PLAYER_HEIGHT <= LEVEL_HEIGHT ) ) {
        mPosY += mVelY;
    }
}

void Player::render( int camX, int camY )
{
    SDL_Rect* currentClip = &gSpriteClips[ frame / 5 ];

    //Show the player relative to the camera
	gPlayerTexture.render( mPosX - camX, mPosY - camY, currentClip );
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Contra - Parallax", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load player texture
	if( !gPlayerTexture.loadFromFile( "resources/Player1.png" ) )
	{
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
	if( !gBGTexture.loadFromFile( "resources/bg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
    if (debug_mode){
        printf("Modo debug habilitado\n");
    }
    //The frame rate regulator
    Timer fps;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The player that will be moving around on the screen
			Player player;

			//The camera area
			SDL_Rect camera = { 0, 0, 800, 600 };
			//While application is running
			while( !quit )
			{
                //Start the frame timer
                fps.start();

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the player
					player.handleEvent( e );
				}

				//Move the player
				player.move();


				//Center the camera over the player
				camera.x = ( player.getPosX() + Player::PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
				camera.y = SCREEN_HEIGHT / 2;


				//Keep the camera in bounds
				if( camera.x < 0 )
				{
					camera.x = 0;
				}
				if( camera.y < 0 )
				{
					camera.y = 0;
				}
				if( camera.x > LEVEL_WIDTH - camera.w )
				{
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if( camera.y > LEVEL_HEIGHT - camera.h )
				{
				    camera.y = LEVEL_HEIGHT - camera.h;
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				gBGTexture.render( 0, 0, &camera);

				//Render objects
				player.render( camera.x, camera.y );

				//Update screen
				SDL_RenderPresent( gRenderer );

                //Go to next frame
				++frame;

				//Cycle animation
				if( frame / WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}


                if((frame / 5 >= 3 ) && (debug_mode)){
                     printf("PosX: %d\nPosY: %d\n\n",player.getPosX(),player.getPosY());
                }


                //If we want to cap the frame rate
                if ( fps.get_ticks() < 1000 / SCREEN_FPS )
                {
                    //Sleep the remaining frame time
                    SDL_Delay( ( 1000 / SCREEN_FPS ) - fps.get_ticks() );
                }
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
