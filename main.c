#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "min_span.h"
#include "shortest_path.h"
#include "search.h"
#include "input.h"

int main(void){
	
	// Initialize the graph
	Graph graph;
	graph.num_vertices = 0;
	graph.num_edges = 0;
	graph.edges =  malloc(sizeof(Edge));
	graph.vertices = malloc(sizeof(Node));
	
	char command[MAX + 1];	// additional +1 for null terminator
	char *c_arr;
	int type = -1;
	int num_tokens = -1;

	int **adjacency_matrix;

	do{
		getInput(command);
		num_tokens = getNumTokens(command);
		
		// skip commands with invalid number of tokens
		if (num_tokens < 1 || num_tokens > 4){
			continue;
		}
		
		c_arr = strtok(command, " ");		// split the string by " " to a string array
		if (c_arr != NULL)
		{
			type = atoi(&c_arr[0]);
		}


		// Execute command
		switch (type){
			
			// Add vertex
			case 1:
				
			// Add Edge
			case 2:
				
			// Get Degree
			case 3:
				
			// Edge-check
			case 4:
				
			// BFS
			case 5:
				
			// DFS
			case 6:
				
			// Path-check
			case 7:

				// generate the adjacency matrix based on current state of the graph
				adjacency_matrix = malloc(graph.num_vertices * sizeof(int *));
				if (adjacency_matrix != NULL){
			
					for (int i = 0; i < graph.num_vertices; i++){
						adjacency_matrix[i] =  calloc(graph.num_vertices, sizeof(int));
					}
					generate_adj_matrix(adjacency_matrix, graph);

					// show result if path exists or not
					printf("%d\n", check_connectivity(&c_arr[1], &c_arr[2], adjacency_matrix));
				
					// free adjacency matrix
					for (int i = 0; i < graph.num_vertices; i++){
						free(adjacency_matrix[i]);
					}
					free(adjacency_matrix);
				}
				break;
			// MST
			case 8:
				
			// Shortest Path (Bonus pla ito)
			case 9:
				
			// Print the graph
			case 10:
				break;
		}
	} while (type != 11);
	free_graph(graph);
	return 0;

}