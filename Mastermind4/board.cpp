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
    // Set "active row" to 0, meaning no space can be clicked yet
    // (this can be changed once we know the dimensions of the screen)
    rowTop = 790;
    rowBot = rowTop+75; //Each peg is 75 pixels vertically from the next peg
    currentRow = 10; // ????

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

/*string Board::checkClick(int x, int y)
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
        currentColor="hole";
    }
    cout << "Curr here: " << currentColor << endl;
    
    return currentColor;
}*/

void Board::nextRow()
{
	cout << "currentRow: " << currentRow << endl;
//	currentRow = ((rowTop-40)/75);

	currentRow--;
	rowTop = rowTop-75;
	rowBot = rowBot-75;
	cout << "currentRow: " << currentRow << endl;
//    currentRow--;
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
	string currentColor;
	if (y <=850 && y >= 814) currentColor = "black";
	else if (y <=770 && y >= 730) currentColor = "red";
	else if (y <=695 && y >= 650) currentColor = "blue";
	else if (y <=620 && y >= 580) currentColor = "green";
	else if (y <=545 && y >= 505) currentColor = "yellow";
	else if (y <=470 && y >= 430) currentColor = "pink";
	cout << "Current color is now: " << currentColor << endl;
    
	return currentColor;
}

void Board::newPegColor(int x, string color) {
	//get column and set color on corresponding peg
	if (x>=315 && x<=405) grid[currentRow][0].setColor(color);
	else if (x>=405 && x<=495) grid[currentRow][1].setColor(color);
	else if (x>=495 && x<=585) grid[currentRow][2].setColor(color);
	else if (x>=585 && x<=675) grid[currentRow][3].setColor(color);
}

/*bool Board::isWinner() {
	int i;
	for (i=0; i<4; i++) {
		if (grid[currentRow][i].getColor() != comp[i].getColor()) return false;
		// ^^^ row color should match comp color for each peg
	}
	return true;
}*/

int Board::getCurrentRow()
{
    return currentRow;
}       
