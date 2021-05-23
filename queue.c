#include "queue.h"


error_t queue_init(struct queue ** out, int num) {
  error_t err = NoErrors;

  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  
  if (NULL == q) {
    err = MemoryError;
    return err;
  }

  q->qu = (int *)malloc(num * sizeof(int));
  
  if (NULL == q->qu) {
    err = MemoryError;
    free(q);
    return err;
  }
  
  q->frnt = 0;
  q->rear = -1;
  q->qmax = num;
  
  *out = q;

  return err;
}

error_t queue_push(struct queue *q, int x) {

  error_t err = NoErrors;

  if (NULL == q) {
    err = InvalidArg;
    return err;
  }

  if (q->rear < q->qmax - 1) {
    q->rear++;
    q->qu[q->rear] = x;
  } else {
    err = MemoryError;
    return err;
  }
  return err;
}

int queue_empty(struct queue *q) {

  if (NULL == q) {
    return 1;
  }

  if (q->rear < q->frnt)
    return 1;
  else
    return 0;
}

error_t queue_print(struct queue *q) {

  error_t err = NoErrors;

  if (queue_empty(q) == 1) {
    err = MemoryError;
    return err;
  }

  int h;
  for (h = q->frnt; h <= q->rear; h++) {
    printf("%d ", q->qu[h]);
  }
  printf("\n");
  
  return err;
}

error_t queue_pop(int* out, struct queue *q) {

  error_t err = NoErrors;
  if (queue_empty(q) == 1) {
    err = MemoryError;
    return err;
  }

  int x, h;
  x = q->qu[q->frnt];
  for (h = q->frnt; h < q->rear; h++) {
    q->qu[h] = q->qu[h + 1];
  }
  q->rear--;
  
  *out = x;

  return err;
}

error_t queue_delete(struct queue *q) {
  error_t err = NoErrors;

  if (NULL == q) {
    err = InvalidArg;
    return err;
  }
  if (NULL == q->qu) {
    err = MemoryError;
    return err;
  }
  free(q->qu);
  free(q);

  return err;
}
