#include "graph.h"

// returns 0 if realloc failed, else returns 1
int resize_vertices(Graph *g){
	Node *v = realloc(g->vertices, sizeof(Node) * (g->num_vertices + 1));
	if (v == NULL){
		return 0;
	}
	else{
		g->vertices = v;
		return 1;
	}
}

// returns 0 if realloc failed, else returns 1
int resize_edges(Graph *g){
	Edge *e = realloc(g->edges, sizeof(Edge) * (g->num_edges + 1));
	if (e == NULL){
		return 0;
	}
	else{
		g->edges = e;
		return 1;
	}
}

void free_graph(Graph *g){
	if (g == NULL){
		return;
	}
	
	if (g->vertices != NULL){
		free(g->vertices);
	}
	
	
	if (g->edges != NULL){
		free(g->edges);
	}
	g->num_edges = 0;
	g->num_vertices = 0;
}

// Returns the index of a node from the graph if it exists,
// else return -1 
int get_node_index(char *target, Graph g){
	if (g.num_vertices == 0){
		return -1;
	}
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
			int t = get_node_index(g.edges[j].node2.key, g);
			if (strcmp( g.edges[j].node1.key, g.vertices[i].key) == 0){
				adj_matrix[i][t] = 1;
			}
			else {
				adj_matrix[i][t] = 0;
			}
		}
	}
	
}

// takes the index of node 1 and node 2, then does a bfs of connections through the
// adjacency matrix to check if a path exists between node 1 and node 2
int check_connectivity(int n1, int n2, int **adj_matrix, int num_vertices){
	int explored[num_vertices];
	
	// set all nodes as unexplored
	for (int i = 0; i < num_vertices; i++){
		explored[i] = 0;
	}
	
	if ( adj_matrix[n1][n2] == 1){
		return 1;
	}
	else
	{
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
			if ( adj_matrix[current_node][child] == 1 && explored[child] != 1){
				explored[child] = 1;
				return travel(target, child, num_vertices, adj_matrix, explored);
			}
		}
		return -1;
		
	}
}

void print_edge(Edge e){
	printf("( %s, %s, %d )", e.node1.key, e.node2.key, e.weight);
}

void print_edges(Edge *edges, int num_edges){
	
	// TODO: sort Edges in lexicographical order
	for (int e = 0; e < num_edges; e++){
		printf("\t");
		print_edge(edges[e]);
		if (e != num_edges - 1) printf(",");
		printf("\n");
	}
}

void print_vertex(Node v){
	
	printf("%s", v.key);
}

void print_vertices(Node *vertices, int num_vertices){
	// TODO: sort Vertices in lexicographical order
	for (int v = 0; v < num_vertices; v++){
		print_vertex(vertices[v]);
		if (v != num_vertices - 1) printf(", ");
	}
}

void print_graph(Graph g){
	
	printf("G = (V, E)\n");
	printf("V = {");
	print_vertices(g.vertices, g.num_vertices);
	printf("}\n");
	printf("E = {\n");
	print_edges(g.edges, g.num_edges);
	printf("}\n");
	
}
