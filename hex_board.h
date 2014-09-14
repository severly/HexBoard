#ifndef HEX_BOARD_H
#define HEX_BOARD_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class hex_board{
private:
	vector< string > board;
	int size;
	
public:
	// Constructor for arbitrary sized board
	hex_board(int s);
	void print();
	int get_size() { return size; }
	void place_piece(bool player, int x, int y);
	int pie_rule(bool player, int x, int y);
	bool is_valid(int x, int y);
};

#endif

