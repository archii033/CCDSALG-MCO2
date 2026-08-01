#include "graph.h"

// returns 0 if realloc failed, else returns 1
int resize_vertices(Graph g){
	Node *v = realloc(g.vertices, sizeof(Node) * (++g.num_vertices));
	if (v == NULL){
		return 0;
	}
	else{
		g.vertices = v;
		return 1;
	}
}

// returns 0 if realloc failed, else returns 1
int resize_edges(Graph g){
	Edge *e = realloc(g.edges, sizeof(Node) * (++g.num_edges));
	if (e == NULL){
		return 0;
	}
	else{
		g.edges = e;
		return 1;
	}
}

void free_graph(Graph g){
	
	// free the node structs
	for (int i = 0; i < g.num_vertices; i++){
		free(&g.vertices[i]);
	}
	free(g.vertices);
	
	// free the edge structs
	for (int i = 0; i < g.num_edges; i++){
		free(&g.edges[i]);
	}
	free(g.edges);
}

// Returns the index of a node from the graph if it exists,
// else return -1 
int get_node_index(char *target, Graph g){
	for (int i = 0; i < g.num_vertices; i++){
		if (strcmp(g.vertices[i].key, target) == 0){
			return i;
		}
	}
	return -1;
}

// each row corresponds to a vertice, and each column represents connection of this vertice
// to some other vertex at that index. 1 for connected, 0 for not connected.
void generate_adj_matrix(int **adj_matrix, Graph g){
	for (int i = 0; i < g.num_vertices; i++){
		// TODO: replace with edge_check
		for (int j = 0; j < g.num_edges; j++){
			if (strcmp( g.edges[j].node1.key, g.vertices[i].key) == 0){
				adj_matrix[i][get_node_index(g.edges[j].node2.key, g)] = 1;
			}
		}
	}
}

// TODO: implement  
int check_connectivity(char key1[], char key2[], int **adj_matrix){
	return -100;
}
