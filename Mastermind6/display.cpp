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
	WIDTH = 800;
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
	WHITE = NULL;
        SOLUTION = NULL;
	WIN = NULL;
	LOSE = NULL;
	CURRENT = NULL;
        INSTRUCTIONS = NULL;
        INST_BUTTON = NULL;
        currentColor = "";
        isLoser = false;
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
	SDL_DestroyTexture(WHITE);
	WHITE = NULL;
	SDL_DestroyTexture(CURRENT);
	CURRENT = NULL;
        SDL_DestroyTexture(SOLUTION);
        SOLUTION = NULL;
	SDL_DestroyTexture(MASTERMIND);
	MASTERMIND = NULL;
        SDL_DestroyTexture(WELCOME);
        WELCOME = NULL;
	SDL_DestroyTexture(WIN);
	WIN = NULL;
	SDL_DestroyTexture(LOSE);
	LOSE = NULL;
        SDL_DestroyTexture(INSTRUCTIONS);
        INSTRUCTIONS = NULL;
        SDL_DestroyTexture(INST_BUTTON);
        INST_BUTTON = NULL;

	//destory renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

/*
//initial screen
void Display::initialShow() {
    
    drawBasics(); //draw background stuff
    drawPegPool(); //draw pegs to chose from (next to board)
    drawPegs(board); //draw pegs (and hints) on board 
    
    //update screen
    rect.x = j;
    rect.y = i;
    rect.w = 56;
    rect.h = 56;
    SDL_RenderSetViewport(renderer, &rect);
    SDL_RenderCopy(renderer, WELCOME, NULL, NULL);
    
//    SDL_RenderPresent (renderer);
    //Was the click on the start button?
    if(x>=25 && x<=185 && y>=750 && y<=840) { //CHANGE THESE #s
        
    }
}
*/

//update screen (based on click)
void Display::update(int x, int y, Board *board) {
    
        //Current click
        cout << endl << "NEW CLICK --> x: " << x << "y: " << y << endl;

	//We have the click. We need to check if it is 
	// 1: the check soln button
	// 2: on one of the pegs in the peg pool
	// 3: in the "active" row (as defined by rowTop and row

	//Was the click on the check solution button?
	if(x>=25 && x<=185 && y>=750 && y<=840) {
		bool valid = board->checkSoln();
		if (valid) {
			board->checkKey();
			if (board->place_hint == 4) {   // All 4 pegs in right spot
                            board->setWinner(true);
			} else if (board->getCurrentRow() < 0) {
                            drawLose();
                        }
		}
	}

        //Was the click on the instructions button?
        if(x>=15 && x<=195 && y>=600 && y<=700) {
            drawInstructions();
        }
	
        //Was the click on one of the pegs in the peg pool?
	else if(x>=210 && x<=266 && y>=425 && y<= HEIGHT) {
		currentColor = board->changeColor(y); //current color as a string
		newCurrCol(currentColor); //set CURRENT to the appropriate texture
	}
	//Was the click on the active row?
	else if(y>=board->rowTop && y<=board->rowBot && x>=200 && x<=WIDTH-100) {
		board->newPegColor(x, currentColor); //get column of clicked peg
	}

	drawBasics(); //draw background stuff
	drawPegPool(); //draw pegs to chose from (next to board)
	drawPegs(board); //draw pegs (and hints) on board 
	
        //update screen
	SDL_RenderPresent (renderer);
}

void Display::drawBasics() {
        //*redraw white background, mastermind logo, check solution button and main board*

	//white screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white, opaque
        SDL_RenderClear(renderer);
       
        //set viewport for board
        SDL_Rect rect;
        rect.x=WIDTH-550; 
        rect.y=0;
        rect.w=550; 
        rect.h=900; 
        SDL_RenderSetViewport(renderer, &rect);
        //render main board to screen
        SDL_RenderCopy(renderer, BOARD, NULL, NULL);

        //set viewport for Mastermind logo
        rect.x=13;
        rect.y=40;
        rect.w=255;
        rect.h=140;
        SDL_RenderSetViewport(renderer, &rect);
        //render Mastermind title to screen
        SDL_RenderCopy(renderer, MASTERMIND, NULL, NULL);

        //set viewport for instructions button
        rect.x=15;
        rect.y=625;
        rect.w=180;
        rect.h=100;
        SDL_RenderSetViewport(renderer, &rect);
        SDL_RenderCopy(renderer, INST_BUTTON, NULL, NULL);

        //set viewport for solution button
        rect.x=15;
        rect.y=750;
        rect.w=180; 
        rect.h=100; 
        SDL_RenderSetViewport(renderer, &rect);
        //render check solution button to screen
        SDL_RenderCopy(renderer, SOLUTION, NULL, NULL);
}

void Display::drawPegPool() {
	//*draw color selection pegs (any other "side" features?)*
        //set viewport
        SDL_Rect pegRect;
        int num;
        for (num=1; num<=6; num++) {
            pegRect.x=WIDTH-590;
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
}

void Display::drawPegs(Board *board) {
	//draw pegs/holes on board
	int i, j, row, col;
	SDL_Rect rect;
	string color;
	for (i=45; i<(HEIGHT-35); i=i+75) { // y coord start at 45 pixels and repeats every 75 pixels
	    for (j=315; j<(WIDTH-150); j=j+90){ // x coordinate start at 315 pixels and repeat every 90 pixels 
		rect.x = j;
		rect.y = i;
		rect.w = 56;
		rect.h = 56;
		SDL_RenderSetViewport(renderer, &rect);
		row = (i-45)/75;
		col = (j-315)/90;
		color = board->grid[row][col].getColor();
                if (color == "hole") SDL_RenderCopy(renderer, HOLE, NULL, NULL);
		else if (color == "black") SDL_RenderCopy(renderer, BLACK, NULL, NULL);
		else if (color == "red") SDL_RenderCopy(renderer, RED, NULL, NULL);
		else if (color == "blue") SDL_RenderCopy(renderer, BLUE, NULL, NULL);
		else if (color == "green") SDL_RenderCopy(renderer, GREEN, NULL, NULL);
		else if (color == "yellow") SDL_RenderCopy(renderer, YELLOW, NULL, NULL);
		else if (color == "pink") SDL_RenderCopy(renderer, PINK, NULL, NULL);
		else SDL_RenderCopy(renderer, HOLE, NULL, NULL);
	    }
	    drawHints(i, row, board); //draw hints for this row
	}
}

void Display::drawHints(int y, int row, Board *board) {
	int i, col = 0, j=y;
	SDL_Rect rect;
	string color;
	for (i=670; i<701; i=i+30) {
		rect.x = i;
		rect.y = j;
		rect.w = 20;
		rect.h = 20;
		SDL_RenderSetViewport(renderer, &rect);
		color = board->hints[row][col].getColor();
		if (color == "red") SDL_RenderCopy(renderer, RED, NULL, NULL);
		else if (color == "white") SDL_RenderCopy(renderer, WHITE, NULL, NULL);
		else SDL_RenderCopy(renderer, HOLE, NULL, NULL);
		j=j+30; // shift y pixel for next hint
		col++; //next column of hints
		rect.x = i;
		rect.y = j;
		rect.w = 20;
		rect.h = 20;
		SDL_RenderSetViewport(renderer, &rect);
		color = board->hints[row][col].getColor();
		if (color == "red") SDL_RenderCopy(renderer, RED, NULL, NULL);
		else if (color == "white") SDL_RenderCopy(renderer, WHITE, NULL, NULL);
		else SDL_RenderCopy(renderer, HOLE, NULL, NULL);
		j=j-30; //reset y pixel for next hint
		col++; //next column of hints

	}
}

void Display::drawInstructions() {
    // white screen   
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white, opaque
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    SDL_Event e;
    int x, y;
    bool quit = false;
    rect.x = 0;
    rect.y = 0;
    rect.w = 800;
    rect.h = 900;

    // load instruction screen
    SDL_RenderSetViewport(renderer, &rect);
    SDL_RenderCopy(renderer, INSTRUCTIONS, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.button.type == SDL_MOUSEBUTTONDOWN){
                x = e.button.x;
                y = e.button.y;
            }
            // Was "back" button clicked?
            if (x>=50 && x<=150 && y>=800 && y<=850){
                quit = true;
            }
        }
    }
}

void Display::drawWin()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white, opaque
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 800;
    rect.h = 900;

    // load winning screen
    SDL_RenderSetViewport(renderer, &rect);
    SDL_RenderCopy(renderer, WIN, NULL, NULL);
    SDL_RenderPresent(renderer);

}

void Display::drawLose(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white, opaque
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    SDL_Event e;
    rect.x = 0;
    rect.y = 0;
    rect.w = 800;
    rect.h = 900;

    // load winning screen
    SDL_RenderSetViewport(renderer, &rect);
    SDL_RenderCopy(renderer, LOSE, NULL, NULL);
    SDL_RenderPresent(renderer);

    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent (&e) != 0) {
            if (e.button.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }
    isLoser = true;
}

bool Display::youLost(){
    bool returnLoser = isLoser;
    isLoser = false;    // set back to false so that game resets
    return returnLoser;
}

//Idk if this function (or CURRENT in general) is necessary.  Is it used anywhere?
void Display::newCurrCol(string color) {
	if (color=="black") CURRENT = BLACK;
	else if (color=="red") CURRENT = RED;
	else if (color=="blue")CURRENT = BLUE;
	else if (color=="green") CURRENT = GREEN;
	else if (color=="yellow") CURRENT = YELLOW;
	else if (color=="pink") CURRENT = PINK;
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
	WHITE = loadTexture("images/white.png");
	MASTERMIND = loadTexture("images/Become-mastermind.png");
        WELCOME = loadTexture("images/welcome.png");
	SOLUTION = loadTexture("images/check-solution.png");
	WIN = loadTexture("images/winScreen1.png"); //or winnerScreen2.png
	LOSE = loadTexture("images/loserScreen.png");
        INSTRUCTIONS = loadTexture("images/instructions.png");
        INST_BUTTON = loadTexture("images/inst_button.png");

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
