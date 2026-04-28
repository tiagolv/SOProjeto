#ifndef MEMORY_H
#define MEMORY_H

#include "sim.h"

void mem_init(void);
int mem_load_program(const char *filename, int *start_out, int *size_out);
void mem_clear_range(int start, int size);
int mem_find_free(int size);

#endif
