#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "errors.h"


struct queue {
  	int *qu;
  	int rear, frnt;
  	int qmax;
};

error_t queue_init(struct queue ** out, int num);
error_t queue_push(struct queue *q, int x);
int queue_empty(struct queue *q);
error_t queue_print(struct queue *q);
error_t queue_pop(int* out, struct queue *q);
error_t queue_delete(struct queue *q);