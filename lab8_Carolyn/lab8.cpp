//Carolyn Bergdolt
//lab 8, introductory SDL stuff
//this program moves tux around the screen, 
//based on where the user clicks.  

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

//global variables
//window dimensions
const int WIDTH = 480;
const int HEIGHT = 360;

//helper functions
//create SDL window
bool init();

//load image
bool load();

//Frees image and shuts down SDL window
void close();

//more global things
//rendering window
SDL_Window* window = NULL;

//window's surface
SDL_Surface* surface = NULL;

//image to load and show on screen
SDL_Surface* TUX = NULL;


int main( int argc, char * args[]) {
	if (!init() || !load()) return 0;
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
		while(SDL_PollEvent (&e)) {
			if (e.type == SDL_QUIT) quit = true;
			if (e.button.type == SDL_MOUSEBUTTONDOWN) {
				x = e.button.x;
				y = e.button.y;

				//set destination blit surface
				SDL_Rect destrect;
				destrect.x = x;
				destrect.y = y;
				destrect.w = 40;
				destrect.h = 60;

				SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
				SDL_BlitSurface(TUX, NULL, surface, &destrect);
				SDL_UpdateWindowSurface(window);
			}
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

		//create window!
		window = SDL_CreateWindow( "Hopping Tux", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
		}
		else {
			//get window surface
			surface=SDL_GetWindowSurface( window );
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
			SDL_UpdateWindowSurface(window);
		}
	}
	return success;
}


bool load() {
	//loading flag initialization
	bool success = true;

	//load image
	TUX = SDL_LoadBMP("tux.bmp");
	if (TUX == NULL) {
		cout << "Image failed to load! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else { 
		SDL_BlitSurface(TUX, NULL, surface, NULL);
		SDL_UpdateWindowSurface(window);
	}

	
	return success;
}


void close() {
	//free image surface (tux) ...why no need to free the other surface?
	SDL_FreeSurface(TUX);
	TUX = NULL;

	//destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}	
