
#include <iostream>
#include "node.h"
using namespace std;
/* 
 * Functions in class Node
 *
 *
 */
 
 // Print the list of adjacent nodes to this node
 // Must dereference the pointer twice, since the adjacency list is made up of pointers,
 // and the iterator itself is a pointer.
 void node::print_list(){
	vector<node*>::iterator vi;
	for(vi = neighbors.begin(); vi != neighbors.end(); ++vi)
				cout << *(*vi) << " ";	
 }
 
 bool node::is_empty(){
	if(p == NONE) return true;
	else return false;
 }
 
// Node Overloading operators
int node::operator==(const node &in) const
{
	if( this->p != in.p) return 0;
    return 1;
}


ostream &operator<<(ostream &output, const node &e)
{
	output << " [c." << e.p;
	output << " (" << e.position.first << ", " << e.position.second << ")] ";
	return output;
}