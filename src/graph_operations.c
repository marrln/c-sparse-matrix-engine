/*
 * graph_operations.c
 *
 * Implementation of sparse graph operations, including node creation,
 * insertion, deletion, bidirectional traversal, and printing of the grid
 * and BFS results.
 */

#include "graph_operations.h"

ArrayNode_ptr create_node(int x_new, int y_new) {
    ArrayNode_ptr new_node = (ArrayNode_ptr)malloc(sizeof(ArrayNode));
    if (new_node == NULL) return NULL;
    new_node->x = x_new;
    new_node->y = y_new;
    new_node->east = new_node->west = new_node->north = new_node->south = NULL;
    new_node->is_in_spanning_tree = false;
    return new_node;
}

void insert_node(GraphNode_ptr V, GraphNode_ptr H, int x_new, int y_new, const int FLAG){
    ArrayNode_ptr aux = H[x_new].neighbors_ptr;
    while (aux != NULL) {
        if (aux->y == y_new) {
            printf("Node (%d,%d) already exists. No insertion performed.\n\n", x_new, y_new);
            return;
        }
        aux = aux->south;
    }

    ArrayNode_ptr new_node_xy = create_node(x_new, y_new);
    if (new_node_xy == NULL) {
        printf("Creation of node (%d,%d) failed.\n", x_new, y_new);
        return;
    }

    ArrayNode_ptr* H_head = insert_horizontal(&H[x_new].neighbors_ptr, new_node_xy);
    ArrayNode_ptr* V_head = insert_vertical(&V[y_new].neighbors_ptr, new_node_xy);
    H[x_new].neighbors_ptr = *H_head;
    V[y_new].neighbors_ptr = *V_head;

    printf("\nNode with (%d,%d) inserted.\n", new_node_xy->x, new_node_xy->y);

    if (x_new != y_new && FLAG == 1){
        ArrayNode_ptr new_node_yx = create_node(y_new, x_new);
        if (new_node_yx == NULL) {
            printf("Creation of node (%d,%d) failed.\n", y_new, x_new);
            return;
        }

        ArrayNode_ptr* H_head = insert_horizontal(&H[y_new].neighbors_ptr, new_node_yx);
        ArrayNode_ptr* V_head = insert_vertical(&V[x_new].neighbors_ptr, new_node_yx);
        H[y_new].neighbors_ptr = *H_head;
        V[x_new].neighbors_ptr = *V_head;

        printf("Node with (%d,%d) inserted.\n", new_node_yx->x, new_node_yx->y);
    }
}

ArrayNode_ptr* insert_horizontal(ArrayNode_ptr* H_head, ArrayNode_ptr new_node){
    ArrayNode_ptr aux;

    if ((*H_head) == NULL) {
        (*H_head) = new_node;
        return H_head;
    } else {
        if (new_node->y < (*H_head)->y) {
            new_node->south = (*H_head);
            new_node->south->north = new_node;
            (*H_head) = new_node;
        } else {
            aux = (*H_head);
            while (aux->south != NULL && aux->south->y < new_node->y) aux = aux->south;
            if (aux->south == NULL) {
                aux->south = new_node;
                new_node->north = aux;
            } else {
                new_node->south = aux->south;
                new_node->north = aux;
                aux->south = new_node;
                new_node->south->north = new_node;
            }
        }
        return H_head;
    }
}

ArrayNode_ptr* insert_vertical(ArrayNode_ptr* V_head, ArrayNode_ptr new_node){
    ArrayNode_ptr aux;

    if ((*V_head) == NULL) {
        (*V_head) = new_node;
        return V_head;
    } else {
        if (new_node->x < (*V_head)->x) {
            new_node->east = (*V_head);
            new_node->east->west = new_node;
            (*V_head) = new_node;
        } else {
            aux = (*V_head);
            while (aux->east != NULL && aux->east->x < new_node->x) aux = aux->east;
            if (aux->east == NULL) {
                aux->east = new_node;
                new_node->west = aux;
            } else {
                new_node->east = aux->east;
                new_node->west = aux;
                aux->east = new_node;
                new_node->east->west = new_node;
            }
        }
        return V_head;
    }
}

ArrayNode_ptr traversal_horizontal(GraphNode_ptr H, int x, int y) {
    ArrayNode_ptr aux = H[x].neighbors_ptr;
    while (aux != NULL) {
        if (aux->y == y) return aux;
        else aux = aux->south;
    }
    return NULL;
}

ArrayNode_ptr traversal_vertical(GraphNode_ptr V, int x, int y) {
    ArrayNode_ptr aux = V[y].neighbors_ptr;
    while (aux != NULL) {
        if (aux->x == x) return aux;
        else aux = aux->east;
    }
    return NULL;
}

void delete_node(GraphNode_ptr V, GraphNode_ptr H, int x_del, int y_del, const int FLAG, const int EXIT) {
    ArrayNode_ptr del_node_xy = NULL;

    if (x_del > y_del) {
        del_node_xy = traversal_horizontal(H, x_del, y_del);
    } else {
        del_node_xy = traversal_vertical(V, x_del, y_del);
    }
    if (del_node_xy == NULL) {
        if (EXIT != 1) printf("Node (%d,%d) does not exist.\nAction is cancelled.\n", x_del, y_del);
        return;
    }

    ArrayNode_ptr* H_head = delete_horizontal(&H[x_del].neighbors_ptr, del_node_xy);
    ArrayNode_ptr* V_head = delete_vertical(&V[y_del].neighbors_ptr, del_node_xy);
    H[x_del].neighbors_ptr = *H_head;
    V[y_del].neighbors_ptr = *V_head;

    free(del_node_xy);
    printf("Node (%d,%d) deleted successfully.\n", x_del, y_del);

    if (x_del != y_del && FLAG == 1) {
        ArrayNode_ptr del_node_yx;
        if (y_del > x_del) {
            del_node_yx = traversal_horizontal(H, y_del, x_del);
        } else {
            del_node_yx = traversal_vertical(V, y_del, x_del);
        }

        if (del_node_yx == NULL) {
            printf("Symmetrical node (%d,%d) does not exist.\n", y_del, x_del);
            return;
        } else {
            ArrayNode_ptr* H_head = delete_horizontal(&H[y_del].neighbors_ptr, del_node_yx);
            ArrayNode_ptr* V_head = delete_vertical(&V[x_del].neighbors_ptr, del_node_yx);
            H[y_del].neighbors_ptr = *H_head;
            V[x_del].neighbors_ptr = *V_head;
            free(del_node_yx);
            printf("Symmetrical node (%d,%d) deleted successfully.\n", y_del, x_del);
        }
    }
}

ArrayNode_ptr* delete_horizontal(ArrayNode_ptr* H_head, ArrayNode_ptr del_node) {
    if (*H_head == del_node) {
        *H_head = del_node->south;
        if (*H_head != NULL) {
            (*H_head)->north = NULL;
        }
        return H_head;
    } else {
        if (del_node->north != NULL) {
            del_node->north->south = del_node->south;
        }
        if (del_node->south != NULL) {
            del_node->south->north = del_node->north;
        }
        return H_head;
    }
}

ArrayNode_ptr* delete_vertical(ArrayNode_ptr* V_head, ArrayNode_ptr del_node) {
    if (*V_head == del_node) {
        *V_head = del_node->east;
        if (*V_head != NULL) {
            (*V_head)->west = NULL;
        }
        return V_head;
    } else {
        if (del_node->west != NULL) {
            del_node->west->east = del_node->east;
        }
        if (del_node->east != NULL) {
            del_node->east->west = del_node->west;
        }
        return V_head;
    }
}

void print_horizontal_list(GraphNode_ptr H, int x, int grid_size) {
    ArrayNode_ptr temp = H[x].neighbors_ptr;

    printf("H[%2d]: ", x);
    for (int y = 0; y < grid_size; y++) {
        int found = 0;
        while (temp != NULL) {
            if (temp->y == y) {
                found = 1;
                break;
            }
            temp = temp->south;
        }
        printf("  %d   ", found);
        temp = H[x].neighbors_ptr;
    }
    printf("\n");
}

void print_vertical_list(GraphNode_ptr V, int y, int grid_size) {
    ArrayNode_ptr temp = V[y].neighbors_ptr;

    printf("V[%2d]: ", y);
    for (int x = 0; x < grid_size; x++) {
        int found = 0;
        while (temp != NULL) {
            if (temp->x == x) {
                found = 1;
                break;
            }
            temp = temp->east;
        }
        printf("  %d   ", found);
        temp = V[y].neighbors_ptr;
    }
    printf("\n");
}

void print_grid(GraphNode_ptr V, int grid_size) {
    printf("      ");
    for (int y = 0; y < grid_size; y++) printf("H[%2d] ", y);
    printf("\n");

    for (int y = 0; y < grid_size; y++) print_vertical_list(V, y, grid_size);
}

void print_bfs_res(GraphNode_ptr V, int grid_size) {
    printf("\nBFS Results:\n");
    for (int i = 0; i < grid_size; i++) {
        GraphNode_ptr current = &V[i];
        if (current->neighbors_ptr != NULL) {
            printf("Node (%d): ", i);
            printf("Color: %c, ", current->color);
            printf("Distance: %d, ", current->distance);
            if (current->predecessor != -1)
                printf("Predecessor: %d", current->predecessor);
            else
                printf("Predecessor: None");
            printf("\n");
        }
    }
}
