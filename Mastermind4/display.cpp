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
    MASTERMIND = NULL;
	window = NULL;
	renderer = NULL;
	BOARD = NULL;
	HOLE = NULL;
	BLACK= NULL;
	RED = NULL;
	BLUE = NULL;
	GREEN = NULL;
    YELLOW = NULL;
    PINK = NULL;
    SOLUTION = NULL;
	//NULLize more colors if added
	CURRENT = NULL;
    currentColor = "";
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
    SDL_DestroyTexture(YELLOW);
    YELLOW = NULL;
    SDL_DestroyTexture(PINK);
    PINK = NULL;
	SDL_DestroyTexture(CURRENT);
	CURRENT = NULL;
    SDL_DestroyTexture(SOLUTION);
    SOLUTION = NULL;
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
    
        //Current click
        cout << endl << "NEW CLICK --> x: " << x << "y: " << y << endl;
        cout << "board->rowTop: " << board->rowTop << endl;
        cout << "board->rowBot: " << board->rowBot << endl;
    
        //Check what action was done in the last click
        if (board->checkClick(x, y) != "noColorSelected") { //Color was selected
            currentColor=board->checkClick(x, y); //Save color selected to currentColor
            cout << "current: " << currentColor << endl;
            if (currentColor=="black") {
                CURRENT = BLACK;
            }
            else if (currentColor=="red") {
                CURRENT = RED;
            }
            else if (currentColor=="blue") {
                CURRENT = BLUE;
            }
            else if (currentColor=="green") {
                CURRENT = GREEN;
            }
            else if (currentColor=="yellow") {
                CURRENT = YELLOW;
            }
            else if (currentColor=="pink") {
                CURRENT = PINK;
            }
        }
        else {  //Peg was selected
            //include some sort of if statement to restrict places where peg is being put
            if (x >=25 && x<=25+160 && y>=750 && y<=750+90) {  //Check solution button was clicked
                //From lines in which check button image is loaded
//                rect.x=25;
//                rect.y=750;
//                rect.w=160; //is there a way to get dimensions of the image?
//                rect.h=90; // for future reference, anyway..
                
                //Check if guess is valid (four pegs in it). If so, check solution here. If not, do something so that it doesn't do the following code.
                    // INSERT CHECK GUESS FUNCTION HERE
                
                //Update rowTop and rowBot to update restrictions for the y-coordinate of the top and bottom of selected row
                cout << "Check solution button was pressed. Variables rowTop and rowBot are being updated." << endl;
                cout << "board->rowTop: " << board->rowTop << endl;
                cout << "board->rowBot: " << board->rowBot << endl;
                board->rowTop=board->rowTop-75;
                board->rowBot=board->rowBot-75;
            }
            else {  //Peg was selected
                //Place pegs (block of code below checks to make sure they are only assigned if they are placed in the right row)
                //set viewport
                SDL_Rect rect;
                rect.x=x;
                rect.y=y;
                rect.w=56; //is there a way to get dimensions of the image?
                rect.h=56; // for future reference, anyway...
                SDL_RenderSetViewport(renderer, &rect);
                //render texture of new peg to screen
                SDL_RenderCopy(renderer, CURRENT, NULL, NULL);
//                }
            }
        }

    //Check if hit one of the holes. If so, assign corresponding grid box the current color.
        int row, col, i, j;
        for (j=315; j<(WIDTH-50); j=j+90){ //x
            for (i=45; i<(HEIGHT-35); i=i+75) { //y
                if (x >= j && x <= j+90 && y >= i && y <= i+90) {
                    if (y<=board->rowBot && y>=board->rowTop) { //Check if in the correct row
                        row = (i-45)/90;
                        col = (j-315)/75;
                        cout << "row: " << row << " column: " << col << endl;
                    
                        board->grid[row][col].color=currentColor; //Assign the peg the corresponding color
                        cout << "Assigned color!" << endl;
                        break;
                    }
                }
            }
        }
    
	//check clickability of location...
	//  if not clickable, return;
	//
	//if (CURRENT == NULL ) {
		//set current to the color clicked
		//check to make sure a color location was actually clicked
	//}
    
	//else {
		//*redraw green background, mastermind logo, and main board*
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //green, opaque
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
        //set viewport
        //SDL_Rect rect;
        rect.x=10;
        rect.y=30;
        rect.w=260; //is there a way to get dimensions of the image?
        rect.h=160; // for future reference, anyway...
        SDL_RenderSetViewport(renderer, &rect);
        //render texture to screen
        SDL_RenderCopy(renderer, MASTERMIND, NULL, NULL);
        //set viewport
        //SDL_Rect rect;
        rect.x=25;
        rect.y=750;
        rect.w=160; //is there a way to get dimensions of the image?
        rect.h=90; // for future reference, anyway...
        SDL_RenderSetViewport(renderer, &rect);
        //render texture to screen
        SDL_RenderCopy(renderer, SOLUTION, NULL, NULL);
    

		//*draw color selection pegs (any other "side" features?)*
        //set viewport
        SDL_Rect pegRect;
        int num;
        for (num=1; num<=6; num++) {
            pegRect.x=WIDTH-490;
            pegRect.y=HEIGHT-75*num-25;
            pegRect.w=56;   //Width and height of images
            pegRect.h=56;
            SDL_RenderSetViewport(renderer, &pegRect);
            //render texture to screen
            if (num==1) {
                SDL_RenderCopy(renderer, BLACK, NULL, NULL);
            }
            if (num==2) {
                SDL_RenderCopy(renderer, RED, NULL, NULL);
            }
            if (num==3) {
                SDL_RenderCopy(renderer, BLUE, NULL, NULL);
            }
            if (num==4) {
                SDL_RenderCopy(renderer, GREEN, NULL, NULL);
            }
            if (num==5) {
                SDL_RenderCopy(renderer, YELLOW, NULL, NULL);
            }
            if (num==6) {
                SDL_RenderCopy(renderer, PINK, NULL, NULL);
            }
        }

		//draw pegs/holes on board
//		int i, j, row
//        int col;
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
			color = board->grid[row][col].getColor();
			    if (color == "hole") {
                    SDL_RenderCopy(renderer, HOLE, NULL, NULL);
			    }
			    else if (color == "black") {
                    SDL_RenderCopy(renderer, BLACK, NULL, NULL);
			    }
			    else if (color == "red") {
                    SDL_RenderCopy(renderer, RED, NULL, NULL);
			    }
			    else if (color == "blue") {
                    SDL_RenderCopy(renderer, BLUE, NULL, NULL);
			    }
			    else if (color == "green") {
                    SDL_RenderCopy(renderer, GREEN, NULL, NULL);
			    }
                else if (color == "yellow") {
                    SDL_RenderCopy(renderer, YELLOW, NULL, NULL);
                }
                else if (color == "pink") {
                    SDL_RenderCopy(renderer, PINK, NULL, NULL);
                }
			    else {
				cout << "Ahhhh!  We have a problem!" << endl;
                cout << "row: " << row << endl;
                cout << "column: " << col << endl;
                cout << "color: " << color << endl;
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
	GREEN = loadTexture("images/green_lime.png");
	YELLOW = loadTexture("images/yellow.png");
	PINK = loadTexture("images/pink.png");
    MASTERMIND = loadTexture("images/mastermind.png");
    SOLUTION = loadTexture("images/solution.png");

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
        
        cout << "Loaded texture!" << endl;
	}
	return newTexture;
}
