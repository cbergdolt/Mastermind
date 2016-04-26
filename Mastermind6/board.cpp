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
    numOfRows = 11;
    rowTop = 790;
    rowBot = rowTop+75; //Each peg is 75 pixels vertically from the next peg
    currentRow = 10; //first active row
    winner = false;   

    // Create grid with holes
    // (peg constructor = peg(color, spot, row)
    int i, j;
    grid.reserve(numOfRows);
    hints.reserve(numOfRows);
    for (i = 0; i < numOfRows; i++) {
        for (j = 0; j < rowSize; j++){
            // Push back peg in spot j, row i
            Peg myPeg("hole", j, i);
	    grid[i].push_back(myPeg); //pegs for main board
	    hints[i].push_back(myPeg); //pegs for hints
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

void Board::resetBoard()
{
    rowTop = 790;
    rowBot = rowTop+75;
    currentRow = 10;
    winner = false;

    // Clear all pegs from board
    int i, j;
    for (i = 0; i < numOfRows; i++) {
        for (j = 0; j < rowSize; j++) {
            grid[i][j].setColor("hole");
            hints[i][j].setColor("hole");
        }
    }

    // Create new computer key
    string colors[] = {"black", "red", "blue", "green", "yellow", "pink" }; //ADD OTHER COLORS????
    srand(unsigned (time(0)));
    // Add computer pegs to comp vector
    for (int k = 0; k < rowSize; k++){
        Peg compPeg(colors[rand()%6], k, numOfRows + 1); 
        comp[k].setColor(colors[rand()%6]);
        cout << "computer peg: " << comp[k].getColor() << endl;
    }
}

void Board::nextRow()
{
    currentRow--; // "activate" next row
    rowTop = rowTop-75; // move row pixel bounds
    rowBot = rowBot-75;
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

    //set hint peg colors for place_hint (red pegs)
    for (i=0; i<place_hint; i++) hints[currentRow][i].setColor("red");
    
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

    //set hint peg colors for color_hint (white pegs)
    for (i=place_hint; i<color_hint; i++) hints[currentRow][i].setColor("white");

    nextRow();
}

bool Board::checkSoln() {
	int i;
	for (i=0; i<rowSize; i++) {
		//if a hole is found in the row
		if (grid[currentRow][i].getColor() == "hole") return false;
	}
	return true;
}

string Board::changeColor(int y) {
	string color;
	if (y <=900 && y >= 790) color = "black";
	else if (y <=790 && y >= 715) color = "red";
	else if (y <=715 && y >= 640) color = "blue";
	else if (y <=640 && y >= 565) color = "green";
	else if (y <=565 && y >= 490) color = "yellow";
	else if (y <=490 && y >= 415) color = "pink";
    
	return color;
}

void Board::newPegColor(int x, string color) {
	//get column and set color on corresponding peg
	if (x>=315 && x<=405) grid[currentRow][0].setColor(color);
	else if (x>=405 && x<=495) grid[currentRow][1].setColor(color);
	else if (x>=495 && x<=585) grid[currentRow][2].setColor(color);
	else if (x>=585 && x<=675) grid[currentRow][3].setColor(color);
}


int Board::getCurrentRow()
{
    return currentRow;
}

bool Board::isWinner()
{
    return winner;
}

void Board::setWinner(bool w)
{
    winner = w;
}
