#ifndef NODE_H
#define NODE_H

#include <vector>
#include <utility>
using namespace std;

// An enumerator type to store the player of each node
enum player{PO, PX, NONE};

class node{

	// Overload the << operator to easily print out the values of an edges
	friend ostream &operator<<(ostream &, const node &);

// Fundamental variables needed to desrcibe a node
private:
	pair<int, int> position;
	int posx, posy;
	player p;
	
public:
	vector<node*> neighbors;
	// Constructor with initial values
	node(int x, int y) : position(x,y),  p(NONE){}
	node(pair<int, int> pos, player p) : position(pos), p(p){};
	
	// Empty constructor
	node() : position(-1,-1),  p(NONE){}
	
	// Sets the location of the node
	void set_node(int x, int y){ position.first = x, position.second = y; }
	// Sets the player of the node. Equivalent to placing a piece
	void set_player(bool c){ p = (player)c; }
	void set_player1(player c){ p = (player)c; }
	// Returns the player of the node (NONE, RED, BLACK)
	player get_player() const{ return p;}
	// Adds pointer to an adjacent node to neighbor list
	void add_neighbor(node *node_ptr){ neighbors.push_back(node_ptr); }
	// Prints the list of adjacent nodes
	void print_list();
	// Retrieve the position of the node, in different forms:
	pair<int, int> get_position(){ return position; }
	int getx(){ return position.first; }
	int gety() {return position.second; }
	
	// Returns 1 if the player of node is NONE, i.e., no piece has been placed yet
	bool is_empty();

	int operator==(const node &in) const;
};

#endif
