#include "scheduler.h"
#include "queue.h"

static int pick_fcfs(void)
{
  return queue_pop(&ready_q);
}

static int pick_priority(void)
{
  int i;
  int best = -1;
  int best_prio = 0;

  for (i = 0; i < ready_q.count; i++)
  {
    int idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
    int prio = pcb_table[idx].priority;
    if (best < 0 || prio < best_prio)
    {
      best = idx;
      best_prio = prio;
    }
  }

  if (best >= 0)
    queue_remove(&ready_q, best);

  return best;
}

static int pick_sjf(void)
{
  int i;
  int best = -1;
  int best_left = 0;

  for (i = 0; i < ready_q.count; i++)
  {
    int idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
    int left = pcb_table[idx].size - (pcb_table[idx].pc - pcb_table[idx].start);
    if (best < 0 || left < best_left)
    {
      best = idx;
      best_left = left;
    }
  }

  if (best >= 0)
    queue_remove(&ready_q, best);

  return best;
}

int scheduler_pick_next(void)
{
  if (queue_is_empty(&ready_q))
    return -1;

  if (policy == SCHED_PRIO)
    return pick_priority();
  if (policy == SCHED_SJF)
    return pick_sjf();
  if (policy == SCHED_RM || policy == SCHED_EDF)
    return pick_priority();

  return pick_fcfs();
}

void scheduler_long(void)
{
  int idx;

  if (queue_is_empty(&blocked_q))
    return;

  idx = queue_pop(&blocked_q);
  pcb_table[idx].state = ST_READY;
  queue_push(&ready_q, idx);
}

const char *scheduler_name(sched_policy p)
{
  if (p == SCHED_PRIO)
    return "PRIO";
  if (p == SCHED_SJF)
    return "SJF";
  if (p == SCHED_RM)
    return "RM";
  if (p == SCHED_EDF)
    return "EDF";
  return "FCFS";
}
