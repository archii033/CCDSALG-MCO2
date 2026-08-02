
#ifndef MIN_SPAN_H	
#define MIN_SPAN_H

#include "graph.h"

void minimum_span(Graph graph);

// Helper functions for minimum_span
void swap(Edge *a, Edge *b);
void quickSortEdges(Graph *graph, int lo, int hi);
int partition(Graph *graph, int lo, int hi);

#endif
