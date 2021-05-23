#include <stdio.h>
#include <stdlib.h>

struct queue {
  	int *qu;
  	int rear, frnt;
  	int qmax;
};

struct queue *queue_init(int num);
void queue_push(struct queue *q, int x);
int queue_empty(struct queue *q);
void queue_print(struct queue *q);
int queue_pop(struct queue *q);
