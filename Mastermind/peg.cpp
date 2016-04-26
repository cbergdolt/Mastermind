// Final Project
// Peg Class
// Maria, Carolyn, Maddie

#include "peg.h"
#include <string>
#include <iostream>
using namespace std;


Peg::Peg()
{
    //set default peg type to hole since no pegs have been assigned
    color = "hole";

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

