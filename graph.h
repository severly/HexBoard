#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include "node.h"
#include "hex_board.h"
using namespace std;

class graph{

public:
	graph(int);
	graph(const graph &g);
	~graph() { release();}
	
	// Mostly for debugging: 
	// Print out each node, it's associated player, and all adjacent nodes
	void print();
	// Print ASCII version of the board
	void board_init(){ bp = new hex_board(size); print_board();}
	void print_board();
	void release();
	void start_game();
	
	int get_size(){ return size; }
	int get_order() { return order; }
	
	bool place(bool which, int x, int y);
	bool pie_rule(pair<int ,int >);
	//Two functions to check for player win and AI win
	bool player_win() {return find_win(user); }
	bool ai_win() {	return find_win(!user); }
	bool get_user(){ return user; }
	
	bool user_move(int x, int y);
	pair<int, int> ai_move();
	node at(pair<int, int> index);
	friend class hex_ai;
	
private:
	vector< vector<node> > nodes;
	int order, size;	// number of nodes
	bool user;
	hex_board *bp;
	
	void generate_neighbors();
	
	// Check if indices are in bounds and if spot is taken
	bool is_valid(int x, int y);
	bool find_win(bool);
	pair<int, int> get_move();
	void rand_user();
	pair<int, int> rand_ai();
};


#endif