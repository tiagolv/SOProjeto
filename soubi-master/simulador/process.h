#ifndef PROCESS_H
#define PROCESS_H

#include "sim.h"

int process_create(const char *prog, int ppid, int priority);
int process_fork(int parent_index, int jump);
int process_exec(int idx, const char *prog);
void process_block(int idx);
void process_ready(int idx);
void process_terminate(int idx);

#endif
