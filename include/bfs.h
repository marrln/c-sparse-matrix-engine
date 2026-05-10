#ifndef BFS_H
#define BFS_H

#include "common.h"

void initialize_queue(Queue* Q);
bool enqueue(Queue* Q, GraphNode_ptr node);
GraphNode_ptr dequeue(Queue* Q);
void bfs(GraphNode_ptr V, GraphNode_ptr H, int source);

#endif // BFS_H
