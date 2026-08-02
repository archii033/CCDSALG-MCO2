#include <stdio.h>

#include "search.h"
#include "queue.h"
#include "stack.h"

// Collects every vertex directly connected to key, stores the names inside
// the names array, then sorts that array lexicographically (insertion sort).
// The graph is undirected, so an edge matches whether key is stored as
// node1 or as node2.
// Returns how many neighbors were found.
static int get_neighbors(char *key, Graph g, char (*names)[NAME_MAX]){
	int count = 0;
	int i, j;
	char temp[NAME_MAX];

	for (i = 0; i < g.num_edges; i++){
		if (strcmp(g.edges[i].node1.key, key) == 0){
			strcpy(names[count], g.edges[i].node2.key);
			count++;
		}
		else if (strcmp(g.edges[i].node2.key, key) == 0){
			strcpy(names[count], g.edges[i].node1.key);
			count++;
		}
	}

	// insertion sort so that ties are broken by lexicographic order
	for (i = 1; i < count; i++){
		strcpy(temp, names[i]);
		j = i - 1;
		while (j >= 0 && strcmp(names[j], temp) > 0){
			strcpy(names[j + 1], names[j]);
			j--;
		}
		strcpy(names[j + 1], temp);
	}

	return count;
}

// Breadth-first search starting from key, using a queue.
// Prints one vertex name per line. When there is a choice between adjacent
// vertices, the lexicographically smaller one is visited first.
// Returns 1 if the traversal completed, 0 if key is not in the graph or if
// memory allocation failed.
int bfs(char key[], Graph graph){
	Queue q;
	int *visited;
	char (*neighbors)[NAME_MAX];
	char current[NAME_MAX];
	int start, count, i, index, ok;

	start = get_node_index(key, graph);
	if (start == -1){
		return 0;
	}

	visited = calloc(graph.num_vertices, sizeof(int));
	neighbors = malloc(sizeof(char[NAME_MAX]) * (graph.num_edges + 1));
	if (visited == NULL || neighbors == NULL){
		free(visited);
		free(neighbors);
		return 0;
	}

	init_queue(&q);

	// the start vertex is marked the moment it is enqueued
	visited[start] = 1;
	ok = enqueue(&q, key);

	while (ok == 1 && dequeue(&q, current) == 1){
		printf("%s\n", current);

		count = get_neighbors(current, graph, neighbors);
		for (i = 0; i < count && ok == 1; i++){
			index = get_node_index(neighbors[i], graph);
			if (index != -1 && visited[index] == 0){
				visited[index] = 1;
				ok = enqueue(&q, neighbors[i]);
			}
		}
	}

	free_queue(&q);
	free(visited);
	free(neighbors);

	return ok;
}

// Depth-first search starting from key, using a stack.
// Prints one vertex name per line. Neighbors are pushed in REVERSE
// lexicographic order so that the smallest one ends up on top of the stack
// and is therefore popped first.
// Returns 1 if the traversal completed, 0 if key is not in the graph or if
// memory allocation failed.
int dfs(char key[], Graph graph){
	Stack s;
	int *visited;
	char (*neighbors)[NAME_MAX];
	char current[NAME_MAX];
	int start, count, i, index, ok;

	start = get_node_index(key, graph);
	if (start == -1){
		return 0;
	}

	visited = calloc(graph.num_vertices, sizeof(int));
	neighbors = malloc(sizeof(char[NAME_MAX]) * (graph.num_edges + 1));
	if (visited == NULL || neighbors == NULL){
		free(visited);
		free(neighbors);
		return 0;
	}

	init_stack(&s);

	// the start vertex is marked the moment it is pushed
	visited[start] = 1;
	ok = push(&s, key);

	while (ok == 1 && pop(&s, current) == 1){
		printf("%s\n", current);

		count = get_neighbors(current, graph, neighbors);
		// loop backwards so the smallest neighbor is pushed last
		for (i = count - 1; i >= 0 && ok == 1; i--){
			index = get_node_index(neighbors[i], graph);
			if (index != -1 && visited[index] == 0){
				visited[index] = 1;
				ok = push(&s, neighbors[i]);
			}
		}
	}

	free_stack(&s);
	free(visited);
	free(neighbors);

	return ok;
}
