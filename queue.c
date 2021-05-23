#include "queue.h"

struct queue *queue_init(int num) {
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  q->qu = (int *)malloc(num * sizeof(int));
  q->frnt = 0;
  q->rear = -1;
  q->qmax = num;
  return q;
}

void queue_push(struct queue *q, int x) {

  if (q->rear < q->qmax - 1) {
    q->rear++;
    q->qu[q->rear] = x;
  } else
    printf("Очередь полна!\n");
  return;
}

int queue_empty(struct queue *q) {

  if (q->rear < q->frnt)
    return 1;
  else
    return 0;
}

void queue_print(struct queue *q) {

  if (queue_empty(q) == 1) {
    printf("Очередь пуста!\n");
    return;
  }

  int h;
  for (h = q->frnt; h <= q->rear; h++) {
    printf("%d ", q->qu[h]);
  }
  printf("\n");
  return;
}

int queue_pop(struct queue *q) {

  if (queue_empty(q) == 1) {
    printf("Очередь пуста!\n");
    return 0;
  }

  int x, h;
  x = q->qu[q->frnt];
  for (h = q->frnt; h < q->rear; h++) {
    q->qu[h] = q->qu[h + 1];
  }
  q->rear--;
  return x;
}
