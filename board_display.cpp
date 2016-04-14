//Carolyn Bergdolt
//lab 8, introductory SDL stuff
//this program moves tux around the screen, 
//based on where the user clicks.  

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //for using png images instead of bmp
#include <iostream>
#include <string>

using namespace std;

//global variables
//window dimensions
const int WIDTH = 700;
const int HEIGHT = 900;

//helper functions
//create SDL window
bool init();

//load image
bool loadMedia();

//Frees image and shuts down SDL window
void close();

//Texture loader
SDL_Texture* loadTexture (string path);

//more global things
//rendering window
SDL_Window* window = NULL;

//window renderer
SDL_Renderer* renderer = NULL;

//window's main surface
//SDL_Surface* surface = NULL;

//images to load and show on screen (textures)
SDL_Texture* BOARD = NULL;
SDL_Texture* BLACK = NULL;
SDL_Texture* RED = NULL;
SDL_Texture* BLUE = NULL;
SDL_Texture* GREEN = NULL;
//probably more eventually...


int main( int argc, char * args[]) {
	if (!init() || !loadMedia()) return 0;
	else {
	    //set main loop flag
	    bool quit = false;

	    //Event handler
	    SDL_Event e;

	    //variables to hold x and y click coordinates
	    int x, y;

	    //while application is running
	    while (!quit) {
		//handle events on queue
		while(SDL_PollEvent (&e) != 0) {
			if (e.type == SDL_QUIT) quit = true;
//			if (e.button.type == SDL_MOUSEBUTTONDOWN) {
//				x = e.button.x;
//				y = e.button.y;
//
//				//set destination blit surface
//				SDL_Rect destrect;
//				destrect.x = x;
//				destrect.y = y;
//				destrect.w = 40;
//				destrect.h = 60;

			//"clear" screen
			SDL_SetRenderDrawColor(renderer, 0, 70, 0, 255);
			SDL_RenderClear(renderer);
			//set viewport
			SDL_Rect board;
			board.x=WIDTH-450;
			board.y=0;
			board.w=450;
			board.h=900;
			SDL_RenderSetViewport(renderer, &board);
			//render texture to screen
			SDL_RenderCopy(renderer, BOARD, NULL, NULL);
			//update screen
			SDL_RenderPresent (renderer);
		}
	    }
	}	
	close();
}

bool init() {
	//initialize success flag
	bool success = true;

	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		cout << "SDL could not initialize! SDL Error:" << SDL_GetError() << endl;
		success = false;
	}
	else {
		//set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			cout << "Linear texture filtering not enabled!" << endl;

		//create window!
		window = SDL_CreateWindow( "Mastermind", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
		}
		else {
			//Create Renderer for window
			renderer=SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer==NULL) {
				cout << "Renderer could not be created! SDL Error " << SDL_GetError() << endl;
				success = false;
			}
			else {
				//Intitialize renderer color
				SDL_SetRenderDrawColor(renderer, 0, 70, 0, 255);
				//Initialize PNG loading
				IMG_Init(IMG_INIT_PNG);
			}
		}
	}
	return success;
}


bool loadMedia() {
	//loading flag initialization
	bool success = true;

	//load image
	BOARD = loadTexture("images/board.png");
	if (BOARD == NULL) {
		cout << "Failed to load texture image!" << endl;
		success = false;
	}
	
	return success;
}

SDL_Texture* loadTexture(string path) {
	//texture to load to and return
	SDL_Texture* newTexture = NULL;

	//load image from specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface==NULL) 
		cout << "Unable to load " << path << " SDL_image Error: " << IMG_GetError() << endl;
	else {
		//set transparent color to white
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
		//create texture from loaded surface
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) 
			cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;

		//Free old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void close() {
	//destroy texture
	SDL_DestroyTexture(BOARD);
	BOARD = NULL;

	//destory renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}	
