
#ifndef GRAPH_H	
#define GRAPH_H

#include <stdlib.h>
#define NAME_MAX 256


typedef struct Node{
	char key[NAME_MAX];
} Node;

typedef struct Edge{
	Node *node1;
	Node *node2;
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
void check_edge(Edge e, Graph graph);
void check_connectivity(char key1[], char key2[], Graph graph);

// Helper functions for the graph structure
int resize_vertices(Graph g);
int resize_edges(Graph g);
void free_graph(Graph g);

#endif