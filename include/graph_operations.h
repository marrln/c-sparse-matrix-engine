#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H

#include "common.h"

ArrayNode_ptr create_node(int x_new, int y_new);
void insert_node(GraphNode_ptr V, GraphNode_ptr H, int x_new, int y_new, const int FLAG);
ArrayNode_ptr* insert_horizontal(ArrayNode_ptr* H_head, ArrayNode_ptr new_node);
ArrayNode_ptr* insert_vertical(ArrayNode_ptr* V_head, ArrayNode_ptr new_node);

ArrayNode_ptr traversal_horizontal(GraphNode_ptr H, int x, int y);
ArrayNode_ptr traversal_vertical(GraphNode_ptr V, int x, int y);

void delete_node(GraphNode_ptr V, GraphNode_ptr H, int x_del, int y_del, const int FLAG, const int EXIT);
ArrayNode_ptr* delete_horizontal(ArrayNode_ptr* H_head, ArrayNode_ptr del_node);
ArrayNode_ptr* delete_vertical(ArrayNode_ptr* V_head, ArrayNode_ptr del_node);

void print_horizontal_list(GraphNode_ptr H, int x, int grid_size);
void print_vertical_list(GraphNode_ptr V, int y, int grid_size);
void print_grid(GraphNode_ptr V, int grid_size);
void print_bfs_res(GraphNode_ptr V, int grid_size);

#endif // GRAPH_OPERATIONS_H
