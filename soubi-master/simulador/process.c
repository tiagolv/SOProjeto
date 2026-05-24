#include "process.h"
#include "memory.h"
#include "queue.h"

static int program_in_use(int start, int skip_idx);

static int find_loaded_program(const char *prog, int skip_idx)
{
  int i;
  for (i = 0; i < MAX_PROC; i++)
  {
    if (i == skip_idx)
      continue;
    if (pcb_table[i].used && pcb_table[i].state != ST_TERMINATED &&
        strncmp(pcb_table[i].nome, prog, MAX_NAME) == 0)
      return i;
  }
  return -1;
}

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
  int existing;

  idx = find_free_pcb();
  if (idx < 0)
    return -1;

  /* reuse program already loaded in memory to avoid duplication */
  existing = find_loaded_program(prog, -1);
  if (existing >= 0)
  {
    start = pcb_table[existing].start;
    size  = pcb_table[existing].size;
  }
  else
  {
    if (mem_load_program(prog, &start, &size) < 0)
      return -1;
  }

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
  int old_start = pcb_table[idx].start;
  int old_size  = pcb_table[idx].size;
  int start = 0;
  int size = 0;
  int existing;

  /* reuse if the target program is already loaded by another live process */
  existing = find_loaded_program(prog, idx);
  if (existing >= 0)
  {
    start = pcb_table[existing].start;
    size  = pcb_table[existing].size;
  }
  else
  {
    if (mem_load_program(prog, &start, &size) < 0)
      return -1;
  }

  /* free old program slot if no other process is still using it */
  if (!program_in_use(old_start, idx))
    mem_clear_range(old_start, old_size);

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
