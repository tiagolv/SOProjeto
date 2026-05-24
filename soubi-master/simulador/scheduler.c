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

static int pick_rm(void)
{
  int i;
  int best = -1;
  int best_period = 0;

  for (i = 0; i < ready_q.count; i++)
  {
    int idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
    int p = pcb_table[idx].period;
    if (best < 0 || (p > 0 && (best_period == 0 || p < best_period)))
    {
      best = idx;
      best_period = p;
    }
  }

  if (best >= 0)
    queue_remove(&ready_q, best);

  return best;
}

static int pick_edf(void)
{
  int i;
  int best = -1;
  int best_dl = 0;

  for (i = 0; i < ready_q.count; i++)
  {
    int idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
    int dl = pcb_table[idx].deadline;
    if (best < 0 || (dl > 0 && (best_dl == 0 || dl < best_dl)))
    {
      best = idx;
      best_dl = dl;
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
  if (policy == SCHED_RM)
    return pick_rm();
  if (policy == SCHED_EDF)
    return pick_edf();

  return pick_fcfs();
}

void scheduler_long(void)
{
  int idx;
  int pos;

  if (queue_is_empty(&blocked_q))
    return;

  /* randomly pick one blocked process to unblock */
  pos = rand() % blocked_q.count;
  idx = blocked_q.items[(blocked_q.head + pos) % MAX_PROC];
  queue_remove(&blocked_q, idx);

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
