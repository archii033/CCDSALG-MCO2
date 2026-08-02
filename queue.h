#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <string.h>
#include "graph.h"	/* for NAME_MAX */

/*
 * Queue of vertex names, implemented as a singly linked list with a
 * front and a rear pointer (dynamic memory allocation).
 * Used by the breadth-first search in search.c
 */
typedef struct QueueNode{
	char key[NAME_MAX];
	struct QueueNode *next;
} QueueNode;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	int size;
} Queue;

/* Sets an empty queue. Call this before any other queue operation. */
void init_queue(Queue *q);

/* Returns 1 if the queue has no elements, 0 otherwise. */
int queue_is_empty(Queue *q);

/* Adds key at the rear. Returns 1 on success, 0 if malloc failed. */
int enqueue(Queue *q, char *key);

/* Removes the front element and copies its name into out.
   Returns 1 on success, 0 if the queue is empty. */
int dequeue(Queue *q, char *out);

/* Frees every node still inside the queue. */
void free_queue(Queue *q);

#endif
