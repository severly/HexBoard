/*
 * hex_board.cpp
 */

#include "hex_board.h"



 // Creates an ASCII hex board
 hex_board::hex_board(int s) : size(s){
	string temp;
	for(int i=0; i<size; i++) temp += "- ";
	for(int i=0; i<size; i++) board.push_back(temp);
 }
 
void hex_board::print(){
    cout << "  ";
	for(int i=0; i<size; i++) cout<< i << " ";
	cout << endl;
	for(int i=0; i<size; i++){
		for(int j=0; j<i; j++) cout << " ";
		cout << i << " ";
		cout << board[i];
		cout << endl;
	}
 }
 
void hex_board::place_piece(bool player, int x, int y){
	// Place x if player 1
	if(player) board[y][2*x] = 'x';
	// Place o if player 0
	else if(!player) board[y][2*x] = 'o';
}
