/*
 * input.c
 *
 * User input helper functions for validating and reading grid coordinates
 * and the BFS source index from stdin.
 */

#include "input.h"

int catch_x(void){ // Catching the x - Coordinate
    int x_catch;
    while (1) {
        if (scanf("%d", &x_catch) == 1 && x_catch >= 0 && x_catch < SIZE) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Invalid x. Please enter an integer value between [0,%d]: \n", SIZE-1);
            while (getchar() != '\n');
        }
    }
    return x_catch;
}

int catch_y(void){ // Catching the y - Coordinate
    int y_catch;
    while (1) {
        if (scanf("%d", &y_catch) == 1 && y_catch >= 0 && y_catch < SIZE) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Invalid y. Please enter an integer value between [0,%d]: \n", SIZE-1);
            while (getchar() != '\n');
        }
    }
    return y_catch;
}

int catch_source(void){ // Catching the source for the BFS
    int source;
    while (1) {
        if (scanf("%d", &source) == 1 && source >= 0 && source < SIZE) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Invalid source. Please enter an integer value between [0,%d]: \n", SIZE-1);
            while (getchar() != '\n');
        }
    }
    return source;
}
