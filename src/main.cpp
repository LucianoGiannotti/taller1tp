//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <src/Timer.h>
//Frames per second
const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//The dimensions of the level
const int LEVEL_WIDTH = 3318;
const int LEVEL_HEIGHT = 600;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//Texture wrapper class
class LTexture
{
    private:
		int mWidth = 0;
		int mHeight = 0;
        SDL_Texture *mTexture = nullptr;
        SDL_Renderer *renderer = nullptr;

		//Deallocates texture
		void free() {
            if(mTexture) {
                SDL_DestroyTexture(mTexture);
                mTexture = nullptr;
                mWidth = 0;
                mHeight = 0;
            }
        }

	public:
        LTexture() {}
        LTexture(SDL_Renderer *r): renderer(r) {}
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

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( !loadedSurface ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} else {
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0x00, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( !newTexture ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		} else {
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return (newTexture != nullptr);
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
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

//The Player that will move around on the screen
class Player
{
    private:
		//The X and Y offsets of the player
		int mPosX = 100;
        int mPosY = 100;

		//The velocity of the player
		int mVelX = 0;
        int mVelY = 0;

        int frame = 0;

        LTexture playerTexture;
        //Walking animation
        static const int walking_animation_frames = 6;
        SDL_Rect spriteClips[ walking_animation_frames ];

    public:
		//The dimensions of the Player
		static const int PLAYER_WIDTH = 23;
		static const int PLAYER_HEIGHT = 34;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 8;
		static const int PLAYER_ACC = 2;

        Player() {}
        Player(SDL_Renderer *r);

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

Player::Player(SDL_Renderer *r)
{
    playerTexture = {r};
	if ( !playerTexture.loadFromFile( "resources/Player1.png" ) ) {
		printf( "Failed to load player texture!\n" );
	} else {
        //Set sprite clips

        //Idle animation
        spriteClips[0].x = 143;
        spriteClips[0].y = 17;
        spriteClips[0].w = 23;
        spriteClips[0].h = 34;

        //Walking animation
        spriteClips[1].x = 146;
        spriteClips[1].y = 134;
        spriteClips[1].w = 23;
        spriteClips[1].h = 34;

        spriteClips[2].x = 169;
        spriteClips[2].y = 134;
        spriteClips[2].w = 20;
        spriteClips[2].h = 34;

        spriteClips[3].x = 192;
        spriteClips[3].y = 134;
        spriteClips[3].w = 20;
        spriteClips[3].h = 34;

        spriteClips[4].x = 215;
        spriteClips[4].y = 134;
        spriteClips[4].w = 23;
        spriteClips[4].h = 34;

        spriteClips[5].x = 238;
        spriteClips[5].y = 43;
        spriteClips[5].w = 23;
        spriteClips[5].h = 34;
	}
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
    mPosX += mVelX;
    if( ( mPosX < 0 ) || ( mPosX + PLAYER_WIDTH > LEVEL_WIDTH ) ) {
        mPosX -= mVelX;
    }

    mPosY += mVelY;
    if( ( mPosY < 0 ) || ( mPosY + PLAYER_HEIGHT > LEVEL_HEIGHT ) ) {
        mPosY -= mVelY;
    }
}

void Player::render( int camX, int camY )
{
    //Go to next frame
    ++frame;

    //Cycle animation
    if (frame / walking_animation_frames >= walking_animation_frames) {
        frame = 0;
    }

    printf("PosX: %d\nPosY: %d\n\n", mPosX , mPosY);

    SDL_Rect* currentClip = &spriteClips[ frame / 5 ];

    //Show the player relative to the camera
	playerTexture.render( mPosX - camX, mPosY - camY, currentClip );
}

class Game {
    private:
        bool is_running = false;
        std::string windowTitle = "Contra - Parallax";
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        LTexture BGTexture;
        Player player;
        Timer fps;
        SDL_Rect camera = { 0, 0, 800, 600 };

        void centerCamera();

    public:
        Game();
        ~Game();

        void handleEvents();
        void update();
        void render();
        void clean();
        void delay();

        bool running() { return is_running; }
};

Game::Game() {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        throw std::runtime_error("SDL could not initialize!");
	}

    //Set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    //Create window
    window = SDL_CreateWindow( windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (!window) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	    SDL_Quit();
        throw std::runtime_error("Window could not be created!");
    }

    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	    SDL_DestroyWindow(window);
	    SDL_Quit();
        throw std::runtime_error("Renderer could not be created!");
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
	    SDL_Quit();
        throw std::runtime_error("SDL_image could not initialize!");
    }

    BGTexture = {renderer};
	//Load first background texture
	if( !BGTexture.loadFromFile( "resources/bg.png" ) ) {
		printf("Failed to load background texture!\n" );
	}
    player = {renderer};
    fps.start();
    is_running = true;
}

Game::~Game() {
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        is_running = false;
    } else {
        player.handleEvent(event);
    }
    player.move();
    centerCamera();
}

void Game::render()
{
    //Clear screen
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );

    //Render background
    BGTexture.render( 0, 0, &camera);

    //Render objects
    player.render( camera.x, camera.y );

    //Update screen
    SDL_RenderPresent( renderer );
}

void Game::centerCamera()
{
    //Center the camera over the player
    camera.x = ( player.getPosX() + Player::PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 ) {
        camera.x = 0;
    }
    if( camera.y < 0 ) {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w ) {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h ) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Game::delay()
{
    //If we want to cap the frame rate
    if ( fps.get_ticks() < 1000 / SCREEN_FPS ) {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / SCREEN_FPS ) - fps.get_ticks() );
    }
}


int main( int argc, char* args[] )
{
    Game game;

    while (game.running()) {
        game.handleEvents();
        game.render();
        game.delay();
    }

	return 0;
}
