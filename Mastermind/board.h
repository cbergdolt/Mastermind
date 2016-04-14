// Final Project
// Board Class

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "peg.h"
#include <vector>
#include <ctime>        // For random # generator
#include <cstdlib>

using namespace std;

class Board
{
    public:
        Board();
    
    private:
        vector<vector <Peg> > grid;     // Grid of all the pegs on the board    
        vector<Peg> comp;        // The computer pegs (the winning key)
        int rowTop;              // The y-coordinate of the top of selected row
        int rowBot;              // The y-coordinate of the bottom of selected row
        int rowSize;             // # of pegs in a row (possibly can be changed depending on difficulty)
        int numOfRows;           // Number of rows, should always be 11
};

// Constructor
Board::Board()
{
    rowSize = 4;
    numOfRows = 10;
    // Set "active row" to 0, meaning no space can be clicked yet
    // (this can be changed once we know the dimensions of the screen)
    rowTop = 0; 
    rowBot = 0;
    // Create grid with white pegs
    // (peg constructor = peg(color, spot, row)
    grid.reserve(numOfRows);
    for (int i = 0; i < numOfRows; i++) 
//  {
        for (int j = 0; j < rowSize; j++){
            // Push back peg in spot j, row i
            Peg myPeg("white", j, i);
            grid[i].push_back(myPeg);
        }
// 	do we need another push back here, to put the row in the grid?
//  }

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



#endif
