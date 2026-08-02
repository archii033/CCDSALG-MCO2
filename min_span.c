#include "min_span.h"

// Gets the minimum spanning tree of the graph using a modified Kruskal's Algorithm
void minimum_span(Graph graph){
	
	Graph result;
	result.num_edges = 0;
	result.num_vertices = 0;
	result.edges =  malloc(sizeof(Edge));
	result.vertices = malloc(sizeof(Node));
	
	int **adj_matrix = malloc(graph.num_vertices * sizeof(int *));
	if (adj_matrix != NULL){
			
		for (int i = 0; i < graph.num_vertices; i++){
			adj_matrix[i] =  calloc(graph.num_vertices, sizeof(int));
		}
	
		// create adjacency matrix with no connections
		for (int i = 0; i < graph.num_vertices; i++){
			for (int j = 0; j < graph.num_vertices; j++){
				
				// prevent self-cycle by assuming it is already connected to itself
					adj_matrix[i][j] = 0;
			}
		}
	
		// sort Edges in ascending order based on weight
		quickSortEdges(&graph, 0, graph.num_edges-1);
	
		int n1, n2;
		int check1, check2;
		Edge current_edge;

		// Examine and add edges
		for (int i = 0; i < graph.num_edges; i++){
			current_edge = graph.edges[i];
			n1 = get_node_index(current_edge.node1.key, graph);
			n2 = get_node_index(current_edge.node2.key, graph);

			// Check if edge creates a cycle
			if (n1 != n2 && check_connectivity(n1, n2, adj_matrix, graph.num_vertices) == 0){
				resize_edges(&result);
				result.edges[result.num_edges++] = current_edge;
				
				if (get_node_index(current_edge.node1.key, result) == -1){
					resize_vertices(&result);
					result.vertices[result.num_vertices++] = current_edge.node1;
				}
				
				if (get_node_index(current_edge.node2.key, result) == -1){
					resize_vertices(&result);
					result.vertices[result.num_vertices++] = current_edge.node2; 
				}
				
				adj_matrix[n1][n2] = 1;
				adj_matrix[n2][n1] = 1;
			}
		}
	}
	
	print_graph(result);
}

// swap function for quickSortEdges
void swap(Edge *a, Edge *b){
	Edge temp = *a;
	*a = *b;
	*b = temp;
}

// a modified sortEdge function that uses weight for sorting
void quickSortEdges(Graph *graph, int lo, int hi){
	if (lo < hi){
		int p = partition(graph, lo, hi);
		quickSortEdges(graph, lo, p-1);
		quickSortEdges(graph, p+1, hi);
	}
}

// a modified partition for quickSortEdges that uses weight as basis
int partition(Graph *graph, int lo, int hi){
	int pivot = hi;
	int i = lo - 1;
	
	for (int j = lo; j < hi; j++){
		if (graph->edges[j].weight < graph->edges[pivot].weight && i != j){
			i++;
			swap(&(graph->edges[i]), &(graph->edges[j]));
		}
	}
	
	swap(&(graph->edges[pivot]), &(graph->edges[i+1]));
	return i+1;
}