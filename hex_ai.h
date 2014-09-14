#ifndef HEX_AI_H
#define HEX_AI_H

#include <utility>
#include <iostream>
#include <cstdlib>
#include "graph.h"

class hex_ai{

public:
static pair<int, int> get_move(graph &g);
static pair<int, int> run_game(graph &gp);

};

#endif