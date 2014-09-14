/*
 *	graph.cpp
 *	All functions related to the Graph class defined in graph.c
 *
 */


#include "graph.h"
#include "node.h"
#include "hex_ai.h"
using namespace std;
 
 /*
 * Constructor: build a graph of n+2 by n+2 nodes. Each node has a player (corresponding to player 1 or 
 * player 2) and a list of all nodes it is connected to (max 6).
 * The two extra rows and columns are used to check for a win condition.
 */
graph::graph(int num) : order(num+2), size(num) {

	// Make the vector big enough to fit every node.
	nodes.resize(order);
	// Create an order*order 2D array of nodes
	for(int i=0; i < order; i++){
		for(int j=0; j<order; j++){
			// Create node with i,j coordinates and push back into vector.
			node tmp(i,j);
			nodes[i].push_back(tmp);
		}
	}
	// Attach each node to it's respective neighbors
	generate_neighbors();
}

graph::graph(const graph &g){
	size = g.size;
	order = g.order;
	user = g.user;
	bp = NULL;
	nodes.resize(order);
	// Create an order*order 2D array of nodes
	for(int i=0; i < order; i++){
		for(int j=0; j<order; j++){
			// Create node with i,j coordinates and push back into vector.
			node tmp(i,j);
			tmp.set_player1(g.nodes[i][j].get_player());
			nodes[i].push_back(tmp);
		}
	}

	// Create new references 
	generate_neighbors();
	
	// for(int i=0; i < order; i++){
		// cout << "list " << i << ": ";
		// for(int j=0; j<order; j++){
			// cout << nodes[i][j].neighbors.size() << " ";
		// }
		// cout <<"\n";
	// }
}

/*
 * Create neighbor list of each node. Figuring out how to identify 
 * the adjacent nodes was the hardest part. I did this by picking certain
 * representative nodes (such as 0,0; 10, 10; 0,10; 10,0; 5,5) and writing down
 * the indices of every node they are connected to. I turned this into an algorithm 
 * which is created below.
 */
void graph::generate_neighbors(){
	for(int i=0; i<order; i++){
		for(int j=0; j<order; j++){
			if(i+1 < order){
				nodes[i][j].add_neighbor(&nodes[i+1][j]);
				if(j-1 >= 0) nodes[i][j].add_neighbor(&nodes[i+1][j-1]);
			}
			if(i-1 >= 0){
				nodes[i][j].add_neighbor(&nodes[i-1][j]);
				if(j+1 < order) nodes[i][j].add_neighbor(&nodes[i-1][j+1]);	
			}
			if(j+1 < order) nodes[i][j].add_neighbor(&nodes[i][j+1]);
			if(j-1 >= 0) nodes[i][j].add_neighbor(&nodes[i][j-1]);
		}	
	}
	
	// Set the special edge nodes for win checking.
	for(int i=0; i<order; i++){
		nodes[0][i].set_player(PX);
		nodes[order-1][i].set_player(PX);
		nodes[i][0].set_player(PO);
		nodes[i][order-1].set_player(PO);
	}
}

void graph::release(){
	// Insert code
}


/* 
 * Functions in class graph
 *
 *
 */
bool graph::place(bool which, int x, int y){
	// Check for valid move and if spot is available
	if(!is_valid(x, y)) return 0;
	// Set the player of the node associated with x,y
	nodes[x+1][y+1].set_player(which);
	// Put piece into ascii board and print board
	if(bp != NULL){
		(*bp).place_piece(which, x, y);
		print_board();
	}
	return 1;
}

// Check if indices are in bounds and if spot is taken
bool graph::is_valid(int x, int y){
	if(x < 0 || x >= size || y < 0 || y >= size) return false;
	if(!nodes[x+1][y+1].is_empty()) return false;
	return true;
}

// Print ASCII version of board
void graph::print_board(){
	if(bp == NULL) return;
	(*bp).print();
}

// Mostly for debugging: 
// Print out each node, it's associated player, and all adjacent nodes
void graph::print(){
	cout << endl;
	for(int i=0; i<order; i++){
		for(int j=0; j<order; j++){
			cout << "Node: " << nodes[i][j] << "List: ";
			// Use print_list function associated with each node.
			nodes[i][j].print_list();
			cout << endl;
		}
	}
}

// Start game, figure out if player wants to go first and if they want to use pie rule
void graph::start_game(){
	int which(-1);
	string input;
	// Figure out whether player goes first or second
	while(which!=0 && which !=1){
		cout << "Would you like to go first (0) or second (1)?\n>";
		getline(cin, input);
		sscanf(input.c_str(), "%d", &which);
	}
	user = (bool) which; // Set player for the rest of the game
	// If user wants to go second, let computer go first and implement pie rule
	pair<int, int> move;
	if(user){
		move = ai_move();
		char ans(0);
		cout << "Would you like to use the pie rule? (y/n)";
		while(ans != 'y' && ans!='n'){
			getline(cin, input);
			sscanf(input.c_str(), "%c", &ans);
		}
		if(ans == 'y'){
			pie_rule(move);
			ai_move();	
		}
	}
}

bool graph::pie_rule(pair<int, int> move){
	int x(move.first), y(move.second);
	// Check that the move is within bounds
	if(x < 0 || x >= size || y < 0 || y >= size) return false;
	// Set the player of the node associated with x,y
	nodes[x+1][y+1].set_player(user);
	(*bp).place_piece(user, x, y);
	print_board();
	return 1;
}

// Functions for the respective players' moves.
bool graph::user_move(int x, int y){
	if(!place(user, x, y)){
		cout << "Graph: Invalid move.\n";
		return 0;
	}
	return 1;
}

void graph::rand_user(){
	pair<int, int> move(-1, -1);
	while(!place(user, move.first, move.second)){
			move.first=rand() %size; move.second = rand() %size;
	}
}

pair<int, int> graph::ai_move(){
	pair<int, int> move;
	move = hex_ai::get_move(*this); 
	if(!place(!user, move.first, move.second)){
			cout << "Cannot place computer's move";
	}else cout << "Computer's move: " << move.first << ", " << move.second << endl;
	return move;
}

pair<int, int> graph::rand_ai(){
	pair<int, int> move(-1, -1);
	while(!place(!user, move.first, move.second)){
			move.first=rand() % size; move.second = rand() %size;
	}
	return move;
}

// Used to simplify indexing in find_win(bool)
node graph::at(pair<int, int> index){ 
	if(index.first > order || index.second > order){
		cout << "Out of bounds: (" << index.first << ", " << index.second << ")\n";
		node tmp;
		return tmp;
	}
	return nodes[index.first][index.second]; 
}


// Essentially a DFS algorithm to find destination node.
bool graph::find_win(bool which){

	pair<int, int> src, dest;
	player p;
	// Based on the input, set function up to look for x win or o win.
	if(!which){ 
		src.first = 1; src.second=0; 
		dest.first = order-2; dest.second = order-1;
		p=PO;
	}else{
		src.first = 0; src.second=1; 
		dest.first = order-1; dest.second = order-2;
		p=PX;
	}

	int curr_sz(1), old_sz(0);
	pair<int, int> curr;
	// Initialize vector of visited vertices as well as a boolean array
	// to easily discern whether a vertex has been visited or not.
	vector< pair<int, int> > visited(order*order);
	bool been_there[order][order];
	// Initialize been_there to false, since we haven't visited any nodes.
	for(int i; i < order; i++){
		for(int j; j < order; j++) been_there[i][j] = false; 
	}
		
	// Add source vertex to visited list and set boolean value to true 
	visited[0] = src;

	been_there[src.first][src.second] = true;
	node *tmp;
	for(int j=0; j!=order*order; j++){
		// We have explored all connections of this node and have not found the destination. Let's bail.
		if(curr_sz == old_sz) return 0;
		old_sz = curr_sz;
		// Walk through the list of visited nodes and search each of their adjacency
		// lists for the destination node.
		for(int i=0; i < curr_sz; i++){
			curr = visited[i];
			// Walk through adjacent nodes of the current node
			for(int l = 0; l < this->at(curr).neighbors.size(); l++){
				tmp = this->at(curr).neighbors[l];
				// Is this node the right player?
				if((*tmp).get_player() == p){
					// Has it been visited?
					if (been_there[(*tmp).getx()][(*tmp).gety()] == false){
						// DO WE HAVE A MATCH?!
						if((*tmp).get_position() == dest){ 
							return 1; // WOOOOO! We have a winner!
						// If it's not a win scenario, push back this node so we can look at it's
						// adjacent nodes later.
						}else{
							visited[curr_sz] = (*tmp).get_position();
							curr_sz++;
							been_there[(*tmp).getx()][(*tmp).gety()] = true;
						}
					}
				}
			}
		}
	}
	return 0;
}
