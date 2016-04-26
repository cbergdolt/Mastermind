// Main Driver Program for the Final Project
// Maria, Carolyn, and Maddie


#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include "board.h"
#include "display.h"

using namespace std;

int main(int argc, char* args[]) {

	//instantiate Display object
	Display display;
	//instantiate Board object
	Board board;

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
				if (board.isWinner()){
                                    display.drawWin();
                                    board.resetBoard();
                                }
                                if (display.youLost()){
                                    board.resetBoard();
                                    display.update(0, 0, &board);
                                }
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
