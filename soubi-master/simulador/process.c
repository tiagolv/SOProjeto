#include "process.h"
#include "memory.h"
#include "queue.h"

static int find_free_pcb(void)
{
  int i;
  for (i = 0; i < MAX_PROC; i++)
  {
    if (!pcb_table[i].used)
      return i;
  }
  return -1;
}

static int program_in_use(int start, int skip_idx)
{
  int i;
  for (i = 0; i < MAX_PROC; i++)
  {
    if (i == skip_idx)
      continue;
    if (pcb_table[i].used && pcb_table[i].state != ST_TERMINATED && pcb_table[i].start == start)
      return 1;
  }
  return 0;
}

int process_create(const char *prog, int ppid, int priority)
{
  int idx;
  int start = 0;
  int size = 0;

  idx = find_free_pcb();
  if (idx < 0)
    return -1;

  if (mem_load_program(prog, &start, &size) < 0)
    return -1;

  pcb_table[idx].used = 1;
  pcb_table[idx].pid = next_pid++;
  pcb_table[idx].ppid = ppid;
  strncpy(pcb_table[idx].nome, prog, MAX_NAME - 1);
  pcb_table[idx].nome[MAX_NAME - 1] = '\0';
  pcb_table[idx].start = start;
  pcb_table[idx].size = size;
  pcb_table[idx].pc = start;
  pcb_table[idx].var = 0;
  pcb_table[idx].priority = priority;
  pcb_table[idx].start_time = tempo;
  pcb_table[idx].cpu_time = 0;
  pcb_table[idx].end_time = -1;
  pcb_table[idx].deadline = 0;
  pcb_table[idx].period = 0;
  pcb_table[idx].state = ST_READY;

  queue_push(&ready_q, idx);
  pcb_count++;
  return idx;
}

int process_fork(int parent_index, int jump)
{
  int idx;
  PCB *parent = &pcb_table[parent_index];

  idx = find_free_pcb();
  if (idx < 0)
    return -1;

  pcb_table[idx] = *parent;
  pcb_table[idx].used = 1;
  pcb_table[idx].pid = next_pid++;
  pcb_table[idx].ppid = parent->pid;
  pcb_table[idx].pc = parent->pc + 1;
  pcb_table[idx].state = ST_READY;
  pcb_table[idx].cpu_time = 0;
  pcb_table[idx].start_time = tempo;

  queue_push(&ready_q, idx);

  parent->pc = parent->pc + jump;
  return idx;
}

int process_exec(int idx, const char *prog)
{
  int start = 0;
  int size = 0;

  if (mem_load_program(prog, &start, &size) < 0)
    return -1;

  strncpy(pcb_table[idx].nome, prog, MAX_NAME - 1);
  pcb_table[idx].nome[MAX_NAME - 1] = '\0';
  pcb_table[idx].start = start;
  pcb_table[idx].size = size;
  pcb_table[idx].pc = start;
  pcb_table[idx].var = 0;
  return 0;
}

void process_block(int idx)
{
  pcb_table[idx].state = ST_BLOCKED;
  queue_push(&blocked_q, idx);
}

void process_ready(int idx)
{
  pcb_table[idx].state = ST_READY;
  queue_push(&ready_q, idx);
}

void process_terminate(int idx)
{
  pcb_table[idx].state = ST_TERMINATED;
  pcb_table[idx].end_time = tempo;
  queue_push(&term_q, idx);

  if (!program_in_use(pcb_table[idx].start, idx))
    mem_clear_range(pcb_table[idx].start, pcb_table[idx].size);
}
