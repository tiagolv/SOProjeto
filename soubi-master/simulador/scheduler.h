#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "sim.h"

int scheduler_pick_next(void);
void scheduler_long(void);
const char *scheduler_name(sched_policy p);

#endif
