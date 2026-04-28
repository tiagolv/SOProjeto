#include "exec.h"
#include "scheduler.h"
#include "process.h"
#include "queue.h"

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
  }

  if (running >= 0 && pcb_table[running].state == ST_RUNNING)
  {
    process_ready(running);
    running = -1;
  }
}
