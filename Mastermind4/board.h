// Final Project
// Board Class interface (see board.cpp for implementation)

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "peg.h"
#include <vector>
#include <ctime>        // For random # generator
#include <cstdlib>

using namespace std;

class Board {
    friend class Display;

    public:
        Board();
        string checkClick();
	void checkKey();        // Check user's guess
        void nextRow();         // increments current row
        int getCurrentRow();    // Returns current row
	bool checkSoln();	// Ensures that the row is full before checkKey() is called
	string changeColor(int y); //determines color clicked on height of click
	void newPegColor(int x, string color);	//determines peg column based on x coord of click
//	bool isWinner();	//checks if current row pegs match comp pegs
        //I think we probably need a deconstructor
    
    private:
        string checkClick(int x, int y);	//Check click. Store CURRENT if color was clicked. 
						//Change color attribute of peg if a hole was selected.
        vector<vector <Peg> > grid;     // Grid of all the pegs on the board
        vector<Peg> comp;        // The computer pegs (the winning key)
        int rowTop;              // The y-coordinate of the top of selected/active row
        int rowBot;              // The y-coordinate of the bottom of selected/active row
        int rowSize;             // # of pegs in a row (possibly can be changed depending on difficulty)
        int numOfRows;           // Number of rows, should always be 11
        int place_hint;          // Number of pegs that are the correct color and spot
        int color_hint;          // Number of pegs that match colors with the computer's sequencie
        int currentRow;          // Row that the user is currently on (the "active" row)
};

#endif
