#ifndef CYCLES_H
#define CYCLES_H

#include "common.h"

void edges_not_in_spanning_tree(GraphNode_ptr V);
void cycle_for_edge(GraphNode_ptr V, int x, int y);
void cycles(GraphNode_ptr V);

#endif // CYCLES_H
