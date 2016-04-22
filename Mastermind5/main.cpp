// Main Driver Program for the Final Project
// Maria, Carolyn, and Maddie


#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include "board.h"
#include "display.h"

using namespace std;

int main(int argc, char* args[]) { //these arguments are necessary for SDL

	//instantiate Display object
	Display display;
	//instantiate Board object
	Board board;

	int change; //returned from update, 1 for peg change, 0 for no change
        if (!display.init() || !display.loadMedia()) return 0;
        else {
		//initial window graphics
		display.update(0, 0, &board);
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
				//if the window x is clicked
				if (e.type == SDL_QUIT) quit = true;	//set exit window status
	//I don't know if we want isWinner here, since we are giving the user the opportunity to play again if they win
//				if (board.isWinner()) quit = true;    // Exits window
                                //if the mouse clicks anywhere on the window
				else if (e.button.type == SDL_MOUSEBUTTONDOWN) {
					x = e.button.x;
					y = e.button.y;
					display.update(x, y, &board);
				}
			}
		}
	}
}
