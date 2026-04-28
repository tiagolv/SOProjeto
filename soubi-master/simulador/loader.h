#ifndef LOADER_H
#define LOADER_H

#include "sim.h"

int loader_read_program(const char *filename, instruction *buf, int max, int *out_count);
int loader_read_plan(const char *filename);
int loader_read_control(const char *filename);

#endif
