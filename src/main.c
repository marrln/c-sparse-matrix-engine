/*
 * main.c
 *
 * Application entry point and menu-driven program logic for the sparse matrix
 * graph engine. It initializes the horizontal and vertical graph structures,
 * handles user commands, and coordinates insertion, deletion, BFS, and cycle
 * detection operations.
 */

#include "common.h"
#include "input.h"
#include "graph_operations.h"
#include "bfs.h"
#include "cycles.h"

static void clear_input_line(void) {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n');
}

static char read_menu_choice(void) {
    int ch;
    do {
        ch = getchar();
        if (ch == EOF) return 'q';
    } while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
    clear_input_line();
    return (char)ch;
}

static void clear_screen(void) {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__unix__) || defined(__APPLE__)
    system("clear");
#else
    for (int i = 0; i < 50; ++i) putchar('\n');
#endif
}

int main(void){
	
	int FLAG = 1; // IF 1, UNDIRECTED GRAPH
	
	int BFS_FLAG = 0; // If 1 we have done BFS in our graph
	
	// OPTIONAL		
	//	printf("Do you want to insert and delete symmetrical nodes? ");
	//	printf("(Undirected vs Directed Graph)\nType 1 for yes and 0 for no: ");
	//	while (1) {
	//        if (scanf("%d", &FLAG) == 1 && (FLAG == 0 || FLAG == 1)) {
	//            while (getchar() != '\n'); 
	//            break; 
	//        } else {
	//            printf("Invalid input. Please choose 1 or 0: ");
	//            while (getchar() != '\n');
	//        }
	//    }
	
	// Initialize vertical and horizontal arrays of GraphNode structures
    GraphNode* V = (GraphNode*)malloc(SIZE * sizeof(GraphNode));  // Vertical array
    GraphNode* H = (GraphNode*)malloc(SIZE * sizeof(GraphNode));  // Horizontal array

    if (V == NULL || H == NULL) {
        printf("Memory allocation failed!\n");
        free(V);
        free(H);
        return 1;  // Exit if memory allocation fails
    }

    // Initialize each node in both arrays
    for (int i = 0; i < SIZE; i++) {
        // Initialize vertical array nodes
        V[i].color = 'w';                // Initially unvisited
        V[i].distance = -1;              // Distance set to -1 (undiscovered)
        V[i].predecessor = -1;           // No predecessor initially
        V[i].neighbors_ptr = NULL;       // No neighbors initially

        // Initialize horizontal array nodes
        H[i].color = 'w';
        H[i].distance = -1;
        H[i].predecessor = -1;
        H[i].neighbors_ptr = NULL;
    }
	
    //			 ---MENU---				//
    char choice = 'n';
	int source;
	
    while(choice != 'q'){
		
		printf("\nCHOOSE:\n");
		printf("-Type *i* to insert a new node.\n");
		printf("-Type *p* if you want to print the whole structure.\n");
		printf("-Type *d* if you want to delete a node.\n");
		printf("-Type *b* if you want to do BFS.\n");
		printf("-Type *c* if you want to find the cycles of the graph.\n");
		printf("-Type *q* if you want to quit (deletes whole structure). \n");
		printf("\nNote: Invalid input will be ignored (previous action remains \"n\").\n");
		printf("\nPrevious Action: %c\n", choice);
		
		if(choice != 'q'){
			
			printf("New Action: ");
			choice = read_menu_choice();
			clear_screen();
			
			if(choice == 'q') printf("\nQUIT\n");
			
			else if (choice == 'd') {
				printf("\nDELETE\n");
				BFS_FLAG = 0;
				printf("What are the coordinates of the node?\n");
				printf("x : ");
				int x_del = catch_x();
				printf("y : ");
				int y_del = catch_y();
				delete_node(V,H,x_del,y_del,FLAG,0);
			}
			else if (choice == 'i') {
				printf("\nINSERT\n");
				BFS_FLAG = 0;
				printf("What are the coordinates of the node?\n");
				printf("x : ");
				int x_new = catch_x();
				printf("y : ");
				int y_new = catch_y();
				insert_node(V,H,x_new,y_new,FLAG);
			}
			else if (choice == 'b') {
				
				printf("\nBFS\n");
				printf("What is the source?\n");
				printf("Source : ");
				source = catch_source();
				bfs(V,H,source);
				print_bfs_res(V, SIZE);
				BFS_FLAG = 1;
			}
			else if (choice == 'c'){
				
				printf("\nCYCLES\n");
				
				if (BFS_FLAG == 1){
					printf("\nSource : %d\n", source);
					edges_not_in_spanning_tree(V);
					cycles(V);
				}
				else {
					printf("\nIn order to find the cycles, do BFS first.\n");
				}	
			}
			else if (choice == 'p') {
				printf("\nPRINT\n");
				print_grid(V,SIZE); 				
			} 
			else {
				choice = 'n'; // no action taken
				printf("\nThere is not such choice.\n");
			}
		}
	}

    // 		---DEALLOCATE MEMORY---			//
    const int EXIT = 1;
    for (int x=0; x<SIZE; x++){
    	for (int y=0; y<SIZE; y++){
    		delete_node(V,H,x,y,0,EXIT);
		} 
	} 
	free(V);
    free(H);
	
	return 0; 
}

