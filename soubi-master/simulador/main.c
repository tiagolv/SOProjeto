#include "sim.h"

static sched_policy parse_policy(const char *s)
{
  if (strcmp(s, "PRIO") == 0)  return SCHED_PRIO;
  if (strcmp(s, "SJF")  == 0)  return SCHED_SJF;
  if (strcmp(s, "RM")   == 0)  return SCHED_RM;
  if (strcmp(s, "EDF")  == 0)  return SCHED_EDF;
  return SCHED_FCFS;
}

int main(int argc, char **argv)
{
  const char *plan_file = "plan.txt";
  const char *control_file = "control.txt";

  if (argc > 1)
    plan_file = argv[1];
  if (argc > 2)
    control_file = argv[2];
  sim_init();

  /* apply CLI overrides after init so sim_init() defaults don't clobber them */
  if (argc > 3)
    time_quantum = atoi(argv[3]);
  if (argc > 4)
    policy = parse_policy(argv[4]);

  sim_run(plan_file, control_file);

  return 0;
}
