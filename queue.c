#include "queue.h"

void init_queue(Queue *q){
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
}

int queue_is_empty(Queue *q){
	if (q->front == NULL){
		return 1;
	}
	return 0;
}

int enqueue(Queue *q, char *key){
	QueueNode *n = malloc(sizeof(QueueNode));

	if (n == NULL){
		return 0;
	}

	strcpy(n->key, key);
	n->next = NULL;

	if (q->rear == NULL){
		// queue was empty, so this node is both the front and the rear
		q->front = n;
	}
	else{
		q->rear->next = n;
	}
	q->rear = n;
	q->size++;

	return 1;
}

int dequeue(Queue *q, char *out){
	QueueNode *temp;

	if (q->front == NULL){
		return 0;
	}

	temp = q->front;
	strcpy(out, temp->key);

	q->front = temp->next;
	if (q->front == NULL){
		// queue became empty, so the rear must not be left dangling
		q->rear = NULL;
	}

	free(temp);
	q->size--;

	return 1;
}

void free_queue(Queue *q){
	char temp[NAME_MAX];

	while (dequeue(q, temp) == 1);
}
