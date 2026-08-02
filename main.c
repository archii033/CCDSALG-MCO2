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
			
	// Initialize Adjacency Matrix
	int **adjacency_matrix;

	// Initialize Variables for Token Extraction
	char command[MAX + 1];	// additional +1 for null terminator
	char *tokenArray[4];
	int type = -1;
	int num_tokens = -1;
	do{
		getInput(command);
		// extract tokens separated by " " and get type
		num_tokens = getTokens(command, tokenArray);
		type = atoi(tokenArray[0]);
		
		// skip commands with invalid number of tokens
		if (num_tokens < 1 || num_tokens > 4){
			continue;
		}

		// Execute command
		switch (type){
			
			// Add vertex
			case 1: {
				Node newNode;

				// prevent duplicate vertices
				if (get_node_index(tokenArray[1], graph) == -1) {

					if (resize_vertices(&graph)) {

						strcpy(newNode.key, tokenArray[1]);

						graph.vertices[graph.num_vertices] = newNode;
						graph.num_vertices++;
					}
				}

				break;
			}

			// Add Edge
			case 2: {
				if (num_tokens != 4)
					break;
		
				// both vertices must already exist
				if (get_node_index(tokenArray[1], graph) == -1 ||
				    get_node_index(tokenArray[2], graph) == -1)
					break;

				// prevent duplicate edges
				if (check_edge(tokenArray[1], tokenArray[2], graph))
					break;

				if (resize_edges(&graph)) {

					strcpy(graph.edges[graph.num_edges].node1.key, tokenArray[1]);
					strcpy(graph.edges[graph.num_edges].node2.key, tokenArray[2]);

					graph.edges[graph.num_edges].weight = atoi(tokenArray[3]);

					graph.num_edges++;
				}

				break;
			}

			// Get Degree
			case 3: {
				int degree = 0;

				if (num_tokens != 2)
					break;

				if (get_node_index(tokenArray[1], graph) == -1)
					break;

				for (int i = 0; i < graph.num_edges; i++) {

					if (strcmp(graph.edges[i].node1.key, tokenArray[1]) == 0 ||
					    strcmp(graph.edges[i].node2.key, tokenArray[1]) == 0) {

						degree++;
					}
				}

				printf("%d\n", degree);

				break;
			}
				
			// Edge-check
			case 4:
				if (num_tokens != 3)
					break;
				printf("%d\n", check_edge(tokenArray[1], tokenArray[2], graph));
				break;

			// BFS
			case 5:
				if (num_tokens != 2)
					break;
				bfs(tokenArray[1], graph);
				break;

			// DFS
			case 6:
				if (num_tokens != 2)
					break;
				dfs(tokenArray[1], graph);
				break;
				
			// Path-check
			case 7:
				// generate adjacency matrix
			adjacency_matrix = malloc(graph.num_vertices * sizeof(int *));
			if (adjacency_matrix != NULL){
			
					for (int i = 0; i < graph.num_vertices; i++){
						adjacency_matrix[i] =  calloc(graph.num_vertices, sizeof(int));
					}
					generate_adj_matrix(adjacency_matrix, graph);
					
					// search for a path
					printf("%d\n", check_connectivity(get_node_index(tokenArray[1], graph), 
													  get_node_index(tokenArray[2], graph), 
													  adjacency_matrix, graph.num_vertices));
				
					// free adjacency matrix
					for (int i = 0; i < graph.num_vertices; i++){
						free(adjacency_matrix[i]);
					}
					free(adjacency_matrix);
				}
				break;
				
			// MST
			case 8:
				minimum_span(graph);
				break;

			// Shortest Path (Bonus pla ito)
			case 9:
				
			// Print the graph
			case 10:
				print_graph(graph);
				break;
		}
	} while (type != 11);
	free_graph(&graph);
	return 0;

}
