#include "exec.h"
#include "scheduler.h"
#include "process.h"
#include "queue.h"

static int should_preempt(int cur)
{
  int i, idx, left, cur_left;

  if (queue_is_empty(&ready_q) || policy == SCHED_FCFS)
    return 0;

  if (policy == SCHED_PRIO)
  {
    for (i = 0; i < ready_q.count; i++)
    {
      idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
      if (pcb_table[idx].priority < pcb_table[cur].priority)
        return 1;
    }
    return 0;
  }

  if (policy == SCHED_SJF)
  {
    cur_left = pcb_table[cur].size - (pcb_table[cur].pc - pcb_table[cur].start);
    for (i = 0; i < ready_q.count; i++)
    {
      idx  = ready_q.items[(ready_q.head + i) % MAX_PROC];
      left = pcb_table[idx].size - (pcb_table[idx].pc - pcb_table[idx].start);
      if (left < cur_left)
        return 1;
    }
    return 0;
  }

  if (policy == SCHED_RM)
  {
    for (i = 0; i < ready_q.count; i++)
    {
      idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
      if (pcb_table[idx].period > 0 &&
          (pcb_table[cur].period == 0 ||
           pcb_table[idx].period < pcb_table[cur].period))
        return 1;
    }
    return 0;
  }

  if (policy == SCHED_EDF)
  {
    for (i = 0; i < ready_q.count; i++)
    {
      idx = ready_q.items[(ready_q.head + i) % MAX_PROC];
      if (pcb_table[idx].deadline > 0 &&
          (pcb_table[cur].deadline == 0 ||
           pcb_table[idx].deadline < pcb_table[cur].deadline))
        return 1;
    }
    return 0;
  }

  return 0;
}

static void exec_instruction(PCB *p)
{
  instruction *ins = &memory[p->pc];

  if (ins->ins == 'M')
  {
    p->var = ins->n;
    p->pc++;
    return;
  }
  if (ins->ins == 'A')
  {
    p->var += ins->n;
    p->pc++;
    return;
  }
  if (ins->ins == 'S')
  {
    p->var -= ins->n;
    p->pc++;
    return;
  }
  if (ins->ins == 'B')
  {
    p->pc++;
    process_block(running);
    return;
  }
  if (ins->ins == 'T')
  {
    process_terminate(running);
    return;
  }
  if (ins->ins == 'C')
  {
    process_fork(running, ins->n);
    return;
  }
  if (ins->ins == 'L')
  {
    process_exec(running, ins->nome);
    return;
  }

  p->pc++;
}

void exec_quantum(void)
{
  int i;

  for (i = 0; i < time_quantum; i++)
  {
    if (running < 0)
    {
      running = scheduler_pick_next();
      if (running < 0)
      {
        sim_tick();
        continue;
      }
      pcb_table[running].state = ST_RUNNING;
    }

    exec_instruction(&pcb_table[running]);
    pcb_table[running].cpu_time++;
    sim_tick();

    if (pcb_table[running].state != ST_RUNNING)
    {
      running = -1;
      break;
    }

    if (pcb_table[running].pc >= pcb_table[running].start + pcb_table[running].size)
    {
      process_terminate(running);
      running = -1;
      break;
    }

    /* preemption: check if a higher-priority candidate arrived this tick */
    if (should_preempt(running))
    {
      process_ready(running);
      running = scheduler_pick_next();
      if (running >= 0)
        pcb_table[running].state = ST_RUNNING;
    }
  }

  if (running >= 0 && pcb_table[running].state == ST_RUNNING)
  {
    process_ready(running);
    running = -1;
  }
}
