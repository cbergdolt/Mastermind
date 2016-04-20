// Final Project
// Peg Class interface (see peg.cpp for implementation)
// Maria, Carolyn, Maddie

#ifndef PEG_H
#define PEG_H

#include <string>
#include <iostream>
using namespace std;

class Peg
{
    friend class Display;
    
    public:
        Peg();                  // Default constructor
        Peg(string clr, int spt, int rw);       // Specify color, spot, and row of peg
        void setColor(string);  // Change color variable of peg
        void setSpot(int);
        void setRow(int);
        string getColor();
        int getSpot();
        int getRow();

    private:
        string color;           // The color of the peg
			//0=hole
			//1=black
			//2=red
			//3=blue
			//4=green
        int spot;               // Placement/column of the peg (e.g. 1, 2, 3, or 4)
        int row;
};

#endif
