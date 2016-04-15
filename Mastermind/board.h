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
	//I think we probably need a deconstructor
    
    private:
        vector<vector <Peg> > grid;     // Grid of all the pegs on the board    
        vector<Peg> comp;        // The computer pegs (the winning key)
        int rowTop;              // The y-coordinate of the top of selected row
        int rowBot;              // The y-coordinate of the bottom of selected row
        int rowSize;             // # of pegs in a row (possibly can be changed depending on difficulty)
        int numOfRows;           // Number of rows, should always be 11
};

#endif
