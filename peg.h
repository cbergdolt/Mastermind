// Final Project
// Peg Class
// Maria, Carolyn, Maddie

#ifndef PEG_H
#define PEG_H

#include <string>
#include <iostream>
using namespace std;

class Peg
{
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
        int spot;               // Placement of the peg (e.g. 1, 2, 3, or 4)
        int row;
};

Peg::Peg()
{
    color = "white";
}

Peg::Peg(string clr, int spt, int rw)
{
    color = clr;
    spot = spt;
    row = rw;
}

void Peg::setColor(string clr)
{ color = clr; }

void Peg::setSpot(int spt)
{ spot = spt; }

void Peg::setRow(int rw)
{ row = rw; }

string Peg::getColor()
{ return color; }

int Peg::getSpot()
{ return spot; }

int Peg::getRow()
{ return row; }


#endif
