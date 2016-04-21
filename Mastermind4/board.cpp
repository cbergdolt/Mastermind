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
    rowTop = 795;
    rowBot = rowTop+56; //Each peg is 56 pixels in diameter
    currentRow = 8;
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
    string colors[] = {"black", "red", "blue", "green", "yellow", "pink" }; //ADD OTHER COLORS????
    srand(unsigned (time(0)));
    // Add computer pegs to comp vector
    for (int k = 0; k < rowSize; k++){
        Peg compPeg(colors[rand()%6], k, numOfRows + 1); 
        comp.push_back(compPeg);
        cout << "computer peg: " << comp[k].getColor() << endl;
    }
}

string Board::checkClick(int x, int y)
{
    string currentColor;
    if (x >= 210 && x <= 266 && y <=850 && y >= 814) {
        currentColor = "black";
    }
    else if (x >= 210 && x <= 266 && y <=770 && y >= 730) {
        currentColor = "red";
    }
    else if (x >= 210 && x <= 266 && y <=695 && y >= 650) {
        currentColor = "blue";
    }
    else if (x >= 210 && x <= 266 && y <=620 && y >= 580) {
        currentColor = "green";
    }
    else if (x >= 210 && x <= 266 && y <=545 && y >= 505) {
        currentColor = "yellow";
    }
    else if (x >= 210 && x <= 266 && y <=470 && y >= 430) {
        currentColor = "pink";
    }
    else {
        currentColor="noColorSelected";
    }
    cout << "Curr here: " << currentColor << endl;
    
    return currentColor;
}

void Board::nextRow()
{
    currentRow--;
}

void Board::checkKey()
{
    place_hint = 0;
    color_hint = 0;

    int i, j, k;
    int num_of_pegs = 4;         // Changes depending on difficulty   
    int comp_colors[6];
    int player_colors[6];
           
    // Check for place matches
    for (i = 0; i < num_of_pegs; i++) {
        if (grid[currentRow][i].getColor() == comp[i].getColor() && grid[currentRow][i].getSpot() == comp[i].getSpot())
            place_hint++;       // player_pegs[i] is in correct position
    }
    
    vector <int> matches;
    matches.push_back(99);
    bool alreadyMatched = false;

    for (j = 0; j < num_of_pegs; j++) { // Go through each player peg
        for (k = 0; k < num_of_pegs; k++) {  // Go through each computer peg
            if (grid[currentRow][j].getColor() == comp[k].getColor()){
                for (vector<int>::iterator it = matches.begin(); it != matches.end(); ++it){
                    if (k == *it)
                        alreadyMatched = true;
                }
                if (!alreadyMatched){
                    color_hint++;
                    matches.push_back(k);       // add current computer peg to matches
                }
                alreadyMatched = false;
            }
        }
    }
}

int Board::getCurrentRow()
{
    return currentRow;
}       
