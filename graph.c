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
