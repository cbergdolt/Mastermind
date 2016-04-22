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
		void update(int x, int y, Board *board); 
		bool init(); // creates SDL window
		bool loadMedia(); //loads images

	private:
		//helper functions
		// VVV texture loader, helps loadMedia()
		SDL_Texture* loadTexture (string path);
		void drawHints(int, int, Board *); //draws the hint pegs into the board
		void drawPegs(Board *); //draws pegs that are currently in the board (and the holes)
		void drawPegPool(); // draws selection pegs to the side of the board
		void drawBasics(); //draws board, BG, check soln button and Mastermind title
		void newCurrCol(string); //sets the CURRENT texture based on input color string
		
		//data members
                string currentColor;
		int WIDTH;
		int HEIGHT;

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
		SDL_Texture* WHITE;
		SDL_Texture* CURRENT; //pointer to current texture
		SDL_Texture* WIN;
		SDL_Texture* LOSE;
		
};

#endif	
