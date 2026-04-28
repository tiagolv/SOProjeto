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

int mem_load_program(const char *filename, int *start_out, int *size_out)
{
  instruction tmp[MAX_MEMORY];
  int count = 0;
  int start;

  if (loader_read_program(filename, tmp, MAX_MEMORY, &count) < 0)
    return -1;

  start = mem_find_free(count);
  if (start < 0)
    return -1;

  memcpy(&memory[start], tmp, sizeof(instruction) * count);
  *start_out = start;
  *size_out = count;
  return 0;
}
