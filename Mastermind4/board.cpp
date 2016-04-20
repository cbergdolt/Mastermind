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
    currentRow = 9;
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
        Peg compPeg(colors[rand()%3], k, numOfRows + 1); 
        comp.push_back(compPeg);
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
    
    // Check for color matches
    for (j = 0; j < num_of_pegs; j++) {
        if (comp[j].getColor() == "black") {
            comp_colors[0]++;
        } else if (comp[j].getColor() == "red") {
            comp_colors[1]++;
        } else if (comp[j].getColor() == "blue") {
            comp_colors[2]++;
        } else if (comp[j].getColor() == "green") {
            comp_colors[3]++;
        } else if (comp[j].getColor() == "yellow") {
            comp_colors[4]++;
        } else if (comp[j].getColor() == "pink") {
            comp_colors[5]++;
        }
             
        if (grid[currentRow][j].getColor() == "black"){
            player_colors[0]++;
        } else if (grid[currentRow][j].getColor() == "red"){
            player_colors[1]++;
        } else if (grid[currentRow][j].getColor() == "blue"){
            player_colors[2]++;
        } else if (grid[currentRow][j].getColor() == "green"){
            player_colors[3]++;
        } else if (grid[currentRow][j].getColor() == "yellow") {
            player_colors[4]++;
        } else if (grid[currentRow][j].getColor() == "pink") {
            player_colors[5]++;
        }
    }
            
    bool match = true;
    for (k = 0; k < 4; k++) {
        if (player_colors[k] - comp_colors[k] == -comp_colors[k])   // computer used a color that player did not use
            match = false;
        if (player_colors[k] - comp_colors[k] == player_colors[k])  // player used a color that computer did not use
            match = false;
        if (match){
            if (player_colors[k] - comp_colors[k] < 0){             // color match, but player didn't use enough
                color_hint += player_colors[k];
            } else if (player_colors[k] - comp_colors[k] == 0){     // computer & player used same amount of color
                color_hint += player_colors[k];
            } else if (player_colors[k] = comp_colors[k] > 0){      // color match, but player used too much
                color_hint += comp_colors[k];
            }
        }
    }
}

int Board::getCurrentRow()
{
    return currentRow;
}       
