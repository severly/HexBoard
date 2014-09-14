#include "hex_ai.h"

pair<int, int> hex_ai::get_move(graph &gp){
	int iterations(1000);
	int aiwins(0), userwins(0);
	pair<int, int> move;
	// Vector to keep count of first move wins. Initialize all counts to zero
	vector< vector<int> > possibilities(gp.size);
	for(int i=0; i< gp.size; i++){
		for(int j=0; j<gp.size; j++){
			possibilities[i].push_back(0);
		}
	}
	cout << "I'm thinking...\n";
	// Run game x amount of times and record the win each time
	for(int i=0; i < iterations; i++){
		move = run_game(gp);
		// Check if AI won
		if(move.first < 0) continue;
		possibilities[move.first][move.second]++;
	}

	// Find out which first move produced the most wins
	int max(0);
	for(int i=0; i< gp.size; i++){
		for(int j=0; j<gp.size; j++){
			if(possibilities[i][j] > max){
				max = possibilities[i][j];
				move.first = i;
				move.second = j;
			}
		}
	}

	cout<< "First move: (" << move.first << ", " << move.second << ")\n";
	return move;
}

// Create a copy of the current board and run a game on it. Report 
// the first move if the AI was a winner.
pair<int, int> hex_ai::run_game(graph &gp){
	pair<int, int> first_move(-1, -1);
	graph tmp(gp);
	int size = tmp.size;
	first_move = tmp.rand_ai();
	int j;
	for(j=0; j < size*size/2; j++){
		tmp.rand_user();
		if(tmp.player_win()){
			// Flag if player won
			first_move.first = -1;
			break;
		}
		tmp.rand_ai();
		if(tmp.ai_win()){
			break;
		}
	}
	return first_move;
}
