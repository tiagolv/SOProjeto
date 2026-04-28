#include "queue.h"

void queue_init(queue_t *q)
{
  q->head = 0;
  q->tail = 0;
  q->count = 0;
}

int queue_is_empty(queue_t *q)
{
  return q->count == 0;
}

int queue_is_full(queue_t *q)
{
  return q->count >= MAX_PROC;
}

int queue_push(queue_t *q, int value)
{
  if (queue_is_full(q))
    return -1;

  q->items[q->tail] = value;
  q->tail = (q->tail + 1) % MAX_PROC;
  q->count++;
  return 0;
}

int queue_pop(queue_t *q)
{
  int value;

  if (queue_is_empty(q))
    return -1;

  value = q->items[q->head];
  q->head = (q->head + 1) % MAX_PROC;
  q->count--;
  return value;
}

int queue_peek(queue_t *q)
{
  if (queue_is_empty(q))
    return -1;

  return q->items[q->head];
}

int queue_remove(queue_t *q, int value)
{
  int i, idx;
  int found = 0;
  queue_t tmp;

  queue_init(&tmp);

  for (i = 0; i < q->count; i++)
  {
    idx = q->items[(q->head + i) % MAX_PROC];
    if (!found && idx == value)
    {
      found = 1;
      continue;
    }
    queue_push(&tmp, idx);
  }

  *q = tmp;
  return found ? 0 : -1;
}
