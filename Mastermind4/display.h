//display.h
//Class of members and functions that Mastermind requires graphically
//Maria, Maddie, and Carolyn

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //for using png images instead of bmp
#include <iostream>
#include <string>
#include "board.h"

using namespace std;

class Display {
//	friend class Board;

	public:
		Display(); //Constructor
		~Display(); //Deconstructor
		// VVV draws new things to the display based on x and y 
		//coordinates of click (passed from the driver)
		void update(int x, int y, Board *); 
		bool init(); // creates SDL window
		bool loadMedia(); //loads images

	private:
		//helper functions
		// VVV texture loader, helps loadMedia()
        string currentColor;
		SDL_Texture* loadTexture (string path);

		//data members
		int WIDTH;
		int HEIGHT;
//        int numGuesses;
        SDL_Window* window; //window to render to
		SDL_Renderer* renderer; //window renderer
		//pointers to the textures that will be loaded from the images
		SDL_Texture* BOARD;
        SDL_Texture* MASTERMIND;
        SDL_Texture* SOLUTION;
		SDL_Texture* HOLE;
		SDL_Texture* BLACK;
		SDL_Texture* RED;
		SDL_Texture* BLUE;
		SDL_Texture* GREEN;
        SDL_Texture* YELLOW;
        SDL_Texture* PINK;
		SDL_Texture* CURRENT; //pointer to current texture
		
};

#endif	
