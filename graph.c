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

// takes the index of node 1 and node 2, then does a dfs of connections through the
// adjacency matrix to check if a path exists between node 1 and node 2
int check_connectivity(int n1, int n2, int **adj_matrix, int num_vertices){
	
	int explored[num_vertices];
	
	// set all nodes as unexplored
	for (int i = 0; i < num_vertices; i++){
		explored[i] = 0;
	}

	// check if target node if a direct child
	if ( adj_matrix[n1][n2] == 1){
		return 1;
	}
	else
	{	// depth-search travel
		return travel(n2, n1, num_vertices, adj_matrix, explored);
	}
	
}

int travel(int target, int current_node, int num_vertices, int **adj_matrix, int *explored){
	
	if (adj_matrix[current_node][target] == 1){
		return 1;
	}
	else
	{
		for (int child = 0; child < num_vertices; child++){
			if ( explored[child] != 1){
				explored[child] = 1;
				return travel(target, child, num_vertices, adj_matrix, explored);
			}
		}
		return -1;
		
	}
}
