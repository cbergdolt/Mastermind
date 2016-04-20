// Final Project
// Board Class implementation (see board.h for interface)

#include <iostream>
#include <vector>
#include "peg.h"
#include "board.h"
#include <vector>
#include <ctime>        // For random # generator
#include <cstdlib>

using namespace std;

// Constructor
Board::Board()
{
    rowSize = 4;
    numOfRows = 10;
    // Set "active row" to 0, meaning no space can be clicked yet
    // (this can be changed once we know the dimensions of the screen)
    rowTop = 0; 
    rowBot = 0;
    // Create grid with holes
    // (peg constructor = peg(color, spot, row)
    int i, j;
    grid.reserve(numOfRows);
    for (i = 0; i < numOfRows; i++) {
        for (j = 0; j < rowSize; j++){
            // Push back peg in spot j, row i
            Peg myPeg("hole", j, i);
	    grid[i].push_back(myPeg);
        }
    }

    // Create Computer key
    // Randomize colors
    string colors[] = {"black", "red", "green", "blue"}; //ADD OTHER COLORS????
    srand(unsigned (time(0)));
    // Add computer pegs to comp vector
    for (int k = 0; k < rowSize; k++){
        Peg compPeg(colors[rand()%3], k, numOfRows + 1); 
        comp.push_back(compPeg);
    }
}

string Board::checkClick(int x, int y)
{
    string currentColor;
    if (x >= 210 && x <= 266 && y <=875 && y >= 819) {
        currentColor = "black";
    }
    else if (x >= 210 && x <= 266 && y <=800 && y >= 744) {
        currentColor = "red";
    }
    else if (x >= 210 && x <= 266 && y <=725 && y >= 669) {
        currentColor = "blue";
    }
    else if (x >= 210 && x <= 266 && y <=650 && y >= 594) {
        currentColor = "green";
    }
    else if (x >= 210 && x <= 266 && y <=575 && y >= 519) {
        currentColor = "yellow";
    }
    else if (x >= 210 && x <= 266 && y <=500 && y >= 444) {
        currentColor = "pink";
    }
    else {
        currentColor="noColorSelected";
    }
    cout << "Curr here: " << currentColor << endl;
    
    return currentColor;
}

