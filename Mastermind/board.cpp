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
    string colors[] = {"black", "red", "green", "blue"};
    srand(unsigned (time(0)));
    // Add computer pegs to comp vector
    for (int k = 0; k < rowSize; k++){
        Peg compPeg(colors[rand()%3], k, numOfRows + 1); 
        comp.push_back(compPeg);
    }
}


