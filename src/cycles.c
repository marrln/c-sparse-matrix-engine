/*
 * cycles.c
 *
 * Cycle detection helpers that report non-spanning-tree graph edges and
 * reconstruct cycles from BFS predecessor paths.
 */

#include "cycles.h"

void edges_not_in_spanning_tree(GraphNode_ptr V){ // O(V)
	printf("\nEdges indicating cycles in the graph:\n");
	int num_found = 0;
    for (int i = 0; i < SIZE; i++) {
        ArrayNode_ptr current = V[i].neighbors_ptr;
        if (V[i].distance != -1){ // Skip both empty and undiscovered GraphNodes
	        while (current != NULL) {
	            // Check if (x, y) is not in the spanning tree
	            if (!(current -> is_in_spanning_tree)) {
	                printf("(%d, %d)\n", current->x, current->y);
	                num_found++;
	            }
	            current = current -> east; // Traverse to the next neighbor
	        }
		}
    }
    if (num_found == 0) printf("None\n");
    else printf("\n\n");
}

void cycle_for_edge(GraphNode_ptr V, int x, int y){ // spanning tree max height is V if spanning tree is a list ? SO O(V)? 
	
	int path_x[SIZE], path_y[SIZE];   // Temporary arrays to store paths for x and y
    int index_x = 0, index_y = 0;

    // Trace path from x to root
    int current_x = x;
    while (current_x != -1) {
        path_x[index_x++] = current_x;
        current_x = V[current_x].predecessor;
    }

    // Trace path from y to root
    int current_y = y;
    while (current_y != -1) {
        path_y[index_y++] = current_y;
        current_y = V[current_y].predecessor;
    }

    // Find the lowest common ancestor by walking back through the paths
    int common_index_x = index_x - 1;
    int common_index_y = index_y - 1;
    
    // Move down until paths diverge
    // common_index_x + 1 and common_index_y + 1 point to the common ancestor (CA)
    while (common_index_x >= 0 && common_index_y >= 0 && path_x[common_index_x] == path_y[common_index_y]) {
        common_index_x--;
        common_index_y--;
    }

    // Print the cycle from x to y through the CA
    printf("Cycle involving edge (%d, %d): ", x, y);

    // Print path from x to CA
    for (int i = 0; i <= common_index_x + 1; i++) {
        printf("%d-", path_x[i]);
    }

    // Print path from CA to y in reverse
    for (int i = common_index_y; i >= 0; i--) {
        printf("%d-", path_y[i]);
    }

    printf("%d\n", x);	
}

void cycles(GraphNode_ptr V) { 
    for (int i = 0; i < SIZE; i++) {
        ArrayNode_ptr current = V[i].neighbors_ptr;
        if (V[i].distance != -1){ // Skip Undiscovered GraphNodes, so O(V)
        	while (current != NULL) {
	            if (!current -> is_in_spanning_tree) {
	                cycle_for_edge(V, current -> x, current -> y); // O(V)
	            }
            	current = current -> east;
        	}
		}
    }
}

