#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include "graph.h"	/* for NAME_MAX */

/*
 * Stack of vertex names, implemented as a singly linked list where the
 * head of the list is the top (dynamic memory allocation).
 * Used by the depth-first search in search.c
 */
typedef struct StackNode{
	char key[NAME_MAX];
	struct StackNode *next;
} StackNode;

typedef struct Stack{
	StackNode *top;
	int size;
} Stack;

/* Sets an empty stack. Call this before any other stack operation. */
void init_stack(Stack *s);

/* Returns 1 if the stack has no elements, 0 otherwise. */
int stack_is_empty(Stack *s);

/* Adds key on top. Returns 1 on success, 0 if malloc failed. */
int push(Stack *s, char *key);

/* Removes the top element and copies its name into out.
   Returns 1 on success, 0 if the stack is empty. */
int pop(Stack *s, char *out);

/* Frees every node still inside the stack. */
void free_stack(Stack *s);

#endif
