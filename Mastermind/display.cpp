//display.cpp (implementation for Display class)
//Class of members and functions that Mastermind requires graphically
//Maria, Maddie, and Carolyn

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //for using png images instead of bmp
#include <iostream>
#include <string>
#include "display.h"

using namespace std;

//Constructor
Display::Display(){
	WIDTH = 700;
	HEIGHT = 900;
	window = NULL;
	renderer = NULL;
	BOARD = NULL;
	HOLE = NULL;
	BLACK= NULL;
	RED = NULL;
	BLUE = NULL;
	GREEN = NULL;
	//NULLize more colors if added
	CURRENT = NULL;
}

//Deconstructor
Display::~Display() {
	//destroy textures
	SDL_DestroyTexture(BOARD);
	BOARD = NULL;
	SDL_DestroyTexture(BLACK);
	BLACK = NULL;
	SDL_DestroyTexture(RED);
	RED = NULL;
	SDL_DestroyTexture(BLUE);
	BLUE = NULL;
	SDL_DestroyTexture(GREEN);
	GREEN = NULL;
	SDL_DestroyTexture(CURRENT);
	CURRENT = NULL;
	SDL_DestroyTexture(HOLE);
	HOLE = NULL;

	//destory renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

//update screen (based on click)
void Display::update(int x, int y, Board *board) {

	//check clickability of location...
	//  if not clickable, return;
	//
	//if (CURRENT == NULL ) {
		//set current to the color clicked
		//check to make sure a color location was actually clicked
	//}
	//else {
		//redraw green background and main board
		SDL_SetRenderDrawColor(renderer, 0, 70, 0, 255); //green, opaque
		SDL_RenderClear(renderer);
		//set viewport
		SDL_Rect rect;
		rect.x=WIDTH-450; 
		rect.y=0;
		rect.w=450; //is there a way to get dimensions of the image?
		rect.h=900; // for future reference, anyway...
		SDL_RenderSetViewport(renderer, &rect);
		//render texture to screen
		SDL_RenderCopy(renderer, BOARD, NULL, NULL);

		//draw color selection pegs (any other "side" features?)
		

		//draw pegs/holes on board
		int i, j, row, col;
		string color;
		for (j=315; j<(WIDTH-50); j=j+90){
		    for (i=45; i<(HEIGHT-35); i=i+75) {
			rect.x = j;
			rect.y = i;
			rect.w = 56;
			rect.h = 56;
			SDL_RenderSetViewport(renderer, &rect);
			row = (i-45)/90;
			col = (j-315)/75;
//			cout << board->grid[row][col].getColor() << endl;
			color = board->grid[row][col].getColor();
			    if (color == "hole") {
				SDL_RenderCopy(renderer, HOLE, NULL, NULL);
//				break;
			    }
			    else if (color == "black") {
				SDL_RenderCopy(renderer, BLACK, NULL, NULL);
//				break;
			    }
			    else if (color == "red") {
				SDL_RenderCopy(renderer, RED, NULL, NULL);
//				break;
			    }
			    else if (color == "blue") {
				SDL_RenderCopy(renderer, BLUE, NULL, NULL);
//				break;
			    }
			    else if (color == "green") {
				SDL_RenderCopy(renderer, GREEN, NULL, NULL);
//				break;
			    }
			    else {
				cout << "Ahhhh!  We have a problem!" << endl;
			    }
		    }
		}

		//update screen
		SDL_RenderPresent (renderer);
	//}
}

//initialize window
bool Display::init() {
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

//load the images
bool Display::loadMedia() {
	//loading flag initialization
	bool success = true;

	//load images
	BOARD = loadTexture("images/board.png");
	HOLE = loadTexture("images/hole.png");
	BLACK = loadTexture("images/black.png");
	RED = loadTexture("images/red.png");
	BLUE = loadTexture("images/blue_dark.png");
	GREEN = loadTexture("images/green.png");
//	RED = loadTexture("images/red.png");
//	RED = loadTexture("images/red.png");
//	RED = loadTexture("images/red.png");
//	RED = loadTexture("images/red.png");

	return success;
}

//load image and convert to texture
SDL_Texture* Display::loadTexture(string path) {
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
