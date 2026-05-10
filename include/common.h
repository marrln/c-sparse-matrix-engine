#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef SIZE
#define SIZE 30
#endif

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

typedef struct ArrayNode* ArrayNode_ptr;
typedef struct ArrayNode {
    int x;
    int y;
    ArrayNode_ptr east, west, north, south;
    bool is_in_spanning_tree;
} ArrayNode;

typedef struct GraphNode* GraphNode_ptr;
typedef struct GraphNode {
    char color;
    int distance;
    int predecessor;
    ArrayNode_ptr neighbors_ptr;
} GraphNode;

typedef struct QueueNode* QueueNode_ptr;
typedef struct QueueNode {
    GraphNode_ptr node;
    QueueNode_ptr next;
} QueueNode;

typedef struct Queue {
    QueueNode_ptr front;
    QueueNode_ptr end;
} Queue;

#endif // COMMON_H
