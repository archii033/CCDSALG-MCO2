
#ifndef GRAPH_H	
#define GRAPH_H

#include <stdlib.h>
#include <string.h>
#define NAME_MAX 256


typedef struct Node{
	char key[NAME_MAX];
} Node;

typedef struct Edge{
	Node node1;
	Node node2;
	int weight;
} Edge;

typedef struct Graph{
	Node *vertices;
	Edge *edges;
	int num_vertices;
	int num_edges;
} Graph;

void add_vertex(Node n, Graph graph);
void add_edge(char key1[], char key2[], int weight, Graph graph);
void get_degree(Graph graph);
int check_edge(char *key1, char *key2, Graph graph);
int check_connectivity(int n1, int n2,  int **adj_matrix, int num_vertices);

// Helper functions for the graph structure
int resize_vertices(Graph *g);
int resize_edges(Graph *g);
void free_graph(Graph *g);
int get_node_index(char *target, Graph g);
void generate_adj_matrix(int **adj_matrix, Graph g);
int travel(int target, int current_node, int num_vertices, int **adj_matrix, int *explored);
#endif
