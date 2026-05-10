/*
 * bfs.c
 *
 * Breadth-first search implementation and queue utilities for traversing the
 * sparse graph and marking spanning tree edges.
 */

#include "bfs.h"
#include "graph_operations.h"

static void destroy_queue(Queue* Q) {
    while (Q->front != NULL) {
        dequeue(Q);
    }
    free(Q);
}

void initialize_queue(Queue* Q) {
    Q -> front = Q -> end = NULL;
}

bool enqueue(Queue* Q, GraphNode_ptr node) {
    QueueNode_ptr new_queue_node = (QueueNode_ptr)malloc(sizeof(QueueNode));
    if (new_queue_node == NULL) {
        fprintf(stderr, "Memory allocation failed while enqueuing.\n");
        return false;
    }
    new_queue_node -> node = node;
    new_queue_node -> next = NULL;
    if (Q -> end == NULL) {
        Q -> front =  Q -> end = new_queue_node;
    } else {
        Q -> end -> next = new_queue_node;
        Q -> end = new_queue_node;
    }
    return true;
}

GraphNode_ptr dequeue(Queue* Q) {
    if (Q -> front == NULL) return NULL;
    QueueNode_ptr temp = Q -> front;
    GraphNode_ptr node = temp -> node;
    Q-> front = Q -> front -> next;
    if (Q -> front == NULL) Q -> end = NULL;
    free(temp);
    return node;
}

void bfs(GraphNode_ptr V, GraphNode_ptr H, int source ) {
	
	// Erase info from a past BFS:
	// Set in_spanning_tree to false for all Edges:
	for (int i = 0; i < SIZE; i++) {
        ArrayNode_ptr current = V[i].neighbors_ptr;
        while (current != NULL) {
            current -> is_in_spanning_tree = false;
            current = current -> east;
        }
    }
	// Set GraphNodes' info to undiscovered:
    for (int i = 0; i < SIZE; i++) {

        V[i].color = 'w';          // Initially unvisited = white ('w')
        V[i].distance = -1;        // Distance set to -1 (undiscovered)
        V[i].predecessor = -1;     // No predecessor
    }
	
	// Initialization of the Queue
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    if (Q == NULL) {
        fprintf(stderr, "Memory allocation failed while initializing BFS queue.\n");
        return;
    }
    initialize_queue(Q);
    
    // Set the Source GraphNode:
	V[source].color = 'g'; 
    V[source].distance = 0; 
    
if (!enqueue(Q, &V[source])) {  // Enqueue source node and check for allocation failure
        destroy_queue(Q);
        return;
    }
	
	// Start Discovering:
    while (Q -> front != NULL) { // While the Queue is not empty
    
        GraphNode_ptr current = dequeue(Q);
        ArrayNode_ptr aux = current -> neighbors_ptr;
        
        while (aux != NULL) { // While we have not reached the end of the list of neighbors
        	
        	GraphNode_ptr neighbor = &V[aux -> x];
        	
            if ( neighbor -> color == 'w') { // If neighbor is white
				neighbor -> color = 'g'; // Mark neighbor as discovered (gray)
                neighbor -> distance = current -> distance + 1;
                neighbor -> predecessor = current -> neighbors_ptr -> y;
                if (!enqueue(Q, neighbor)) { // Enqueue neighbor and check for allocation failure
                    destroy_queue(Q);
                    return;
                }

                aux -> is_in_spanning_tree = true;
                
                // Symmetrical edge (y, x) is also in the spanning tree:
                ArrayNode_ptr sym_aux;
                if (aux -> x < aux -> y) {
                    sym_aux = traversal_horizontal(H, aux -> y, aux -> x);
                } else {
                    sym_aux = traversal_vertical(V, aux -> y, aux -> x);
                }
                if (sym_aux != NULL) sym_aux -> is_in_spanning_tree = true;
            }
            aux = aux -> east; // Find the next neighbor
        }
        current -> color = 'b'; // Mark node as fully processed (black) 
    }
    
    // Update H array with the correct info too.
        for (int i = 0; i < SIZE; i++){
        	H[i].color = V[i].color;
        	H[i].distance = V[i].distance;
        	H[i].predecessor = V[i].predecessor;
		}
        
    free(Q);
}

