/*
 *
 *  To run, type in make, then ./main
 */
 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <sstream>
#include <cstdio>

#include "graph.h"
#include "hex_board.h"
#include "hex_ai.h"
using namespace std;


int main(){
	srand(time(NULL));
	// Get the size of the board from user input, then initialize the ASCII board and the 
	// graph with this size.
	int size(-1); // Initialize to an impossible value
	int x, y;
	string input;
	while(size < 1){
		cout << "Enter size of board.\n>";
		getline(cin, input);
		sscanf(input.c_str(), "%d", &size);
	}
	
	// Connected graph representation to run algorithms on
	graph g(size);
	g.board_init(); // Set up ASCII board
	// Pie rule, etc
	g.start_game();

	
	// Play the game!
	pair<int, int> move;
	while(true){
		// Set these to a non-valid value, so if scanf doesn't work we'll catch it.
		x=-1, y=-1;
		// Get the user's input, and use sscanf to extract the numbers
		cout << "Please enter a move: (x, y)\n>";
		getline(cin, input);
		sscanf(input.c_str(), "%d, %d", &x, &y);
		// Check for valid mvoe and place piece
		if(!g.user_move(x, y)) continue;
		if(g.player_win()){
			cout << "Congratulations! Winner!" << endl;
			break;
		}
		// AI Move and win checking
		g.ai_move();
		if(g.ai_win()){
			cout << "You have been defeated by the computer!" << endl;
			break;
		}
		cout <<endl;
	}

}
