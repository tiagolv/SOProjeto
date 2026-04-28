#ifndef QUEUE_H
#define QUEUE_H

#include "sim.h"

void queue_init(queue_t *q);
int queue_is_empty(queue_t *q);
int queue_is_full(queue_t *q);
int queue_push(queue_t *q, int value);
int queue_pop(queue_t *q);
int queue_peek(queue_t *q);
int queue_remove(queue_t *q, int value);

#endif
