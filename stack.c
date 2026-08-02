#include "stack.h"

void init_stack(Stack *s){
	s->top = NULL;
	s->size = 0;
}

int stack_is_empty(Stack *s){
	if (s->top == NULL){
		return 1;
	}
	return 0;
}

int push(Stack *s, char *key){
	StackNode *n = malloc(sizeof(StackNode));

	if (n == NULL){
		return 0;
	}

	strcpy(n->key, key);
	n->next = s->top;
	s->top = n;
	s->size++;

	return 1;
}

int pop(Stack *s, char *out){
	StackNode *temp;

	if (s->top == NULL){
		return 0;
	}

	temp = s->top;
	strcpy(out, temp->key);
	s->top = temp->next;

	free(temp);
	s->size--;

	return 1;
}

void free_stack(Stack *s){
	char temp[NAME_MAX];

	while (pop(s, temp) == 1);
}
