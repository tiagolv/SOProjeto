#include "memory.h"
#include "loader.h"

void mem_init(void)
{
  memset(memory, 0, sizeof(memory));
}

int mem_find_free(int size)
{
  int i, j;
  int ok;

  for (i = 0; i <= MAX_MEMORY - size; i++)
  {
    ok = 1;
    for (j = 0; j < size; j++)
    {
      if (memory[i + j].ins != 0)
      {
        ok = 0;
        break;
      }
    }
    if (ok)
      return i;
  }
  return -1;
}

void mem_clear_range(int start, int size)
{
  int i;

  for (i = 0; i < size; i++)
  {
    memory[start + i].ins = 0;
    memory[start + i].n = 0;
    memory[start + i].nome[0] = '\0';
  }
}

void mem_compact(void)
{
  int i, j;
  int starts[MAX_PROC];
  int sizes[MAX_PROC];
  int new_starts[MAX_PROC];
  int nseg = 0;
  int new_pos = 0;

  /* collect unique live program segments */
  for (i = 0; i < MAX_PROC; i++)
  {
    int dup;
    if (!pcb_table[i].used || pcb_table[i].state == ST_TERMINATED)
      continue;
    dup = 0;
    for (j = 0; j < nseg; j++)
      if (starts[j] == pcb_table[i].start) { dup = 1; break; }
    if (!dup)
    {
      starts[nseg] = pcb_table[i].start;
      sizes[nseg]  = pcb_table[i].size;
      nseg++;
    }
  }

  /* sort segments by start address */
  for (i = 0; i < nseg - 1; i++)
    for (j = i + 1; j < nseg; j++)
      if (starts[j] < starts[i])
      {
        int t;
        t = starts[i]; starts[i] = starts[j]; starts[j] = t;
        t = sizes[i];  sizes[i]  = sizes[j];  sizes[j]  = t;
      }

  /* move blocks to compacted positions */
  for (i = 0; i < nseg; i++)
  {
    new_starts[i] = new_pos;
    if (new_pos != starts[i])
      memmove(&memory[new_pos], &memory[starts[i]],
              sizeof(instruction) * sizes[i]);
    new_pos += sizes[i];
  }

  /* zero the freed tail */
  if (new_pos < MAX_MEMORY)
    memset(&memory[new_pos], 0,
           sizeof(instruction) * (MAX_MEMORY - new_pos));

  /* update all live PCBs */
  for (i = 0; i < MAX_PROC; i++)
  {
    if (!pcb_table[i].used || pcb_table[i].state == ST_TERMINATED)
      continue;
    for (j = 0; j < nseg; j++)
    {
      if (pcb_table[i].start == starts[j])
      {
        int delta = new_starts[j] - starts[j];
        pcb_table[i].start += delta;
        pcb_table[i].pc    += delta;
        break;
      }
    }
  }
}

int mem_load_program(const char *filename, int *start_out, int *size_out)
{
  instruction tmp[MAX_MEMORY];
  int count = 0;
  int start;

  if (loader_read_program(filename, tmp, MAX_MEMORY, &count) < 0)
    return -1;

  start = mem_find_free(count);
  if (start < 0)
  {
    mem_compact();
    start = mem_find_free(count);
    if (start < 0)
      return -1;
  }

  memcpy(&memory[start], tmp, sizeof(instruction) * count);
  *start_out = start;
  *size_out = count;
  return 0;
}
