// Program that checks player's guess with computer's answer

#include <iostream>
using namespace std;


/* VARIABLES:
 * comp_pegs[i] = array of computer's pegs (i=0 goes on left, i=3 goes on right)
 *
 * player_pegs[i] = array of player's guesses (i=0 goes on left, i=3 goes on right)
 *
 * color_hint = # of player's pegs that match computer's colors
 * place_hint = # of player's pegs that are correct color and placement
 *
 * comp_colors[i] = array of number of each color used in computer sequence
 * i = 0 = black, i = 1 = red, i = 2 = green, i = 3 = blue
 *
 * player_colors[i] = same as comp_colors[i]
*/


int main()
{
    // Peg player_pegs[i], comp_pegs[i]
    int i, j, k;
    int num_of_pegs = 4;         // Changes depending on difficulty   
    
    // Check for place matches
    for (i = 0; i < num_of_pegs; i++) {
        if (player_pegs[i].getColor == comp_pegs[i].getColor && player_pegs[i].getSpot == comp_pegs[i].getSpot)
            place_hint++;       // player_pegs[i] is in correct position
    }

    // Check for color matches
    for (j = 0; j < num_of_pegs; j++) {
        if (comp_pegs[j].color == BLACK || player_pegs[j].color == BLACK){
            comp_colors[0]++;
            player_colors[0]++;
        } else if (comp_pegs[j].color == RED || player_pegs[j].color == RED){
            comp_colors[1]++;
            player_colors[1]++;
        } else if (comp_pegs[j].color == GREEN || player_pegs[j].color == GREEN){
            comp_colors[2]++;
            player_colors[2]++;
        } else if (comp_pegs[j].color == BLUE || player_pegs[j].color == BLUE){
            comp_colors[3]++;
            player_colors[3]++;
        }
    }
    
    bool match = TRUE;
    for (k = 0; k < 4; k++) {
        if (player_colors[k] - comp_colors[k] == -comp_colors[k])   // computer used a color that player did not use
            match = FALSE;
        if (player_colors[k] - comp_colors[k] == player_colors[k])  // player used a color that computer did not use
            match = FALSE;
        if (match){
            if (player_colors[k] - comp_colors[k] < 0){             // color match, but player didn't use enough
                color_hint += player_colors[k];
            } else if (player_colors[k] - comp_colors[k] == 0){     // computer & player used same amount of color
                color_hint += player_colors[k];
            } else if (player_colors[k] = comp_colors[k] > 0){      // color match, but player used too much
                color_hint += comp_colors;
            }
        }
    }


    return 0;
}
