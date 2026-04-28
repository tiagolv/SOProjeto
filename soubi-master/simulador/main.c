#include "sim.h"

int main(int argc, char **argv)
{
  const char *plan_file = "plan.txt";
  const char *control_file = "control.txt";

  if (argc > 1)
    plan_file = argv[1];
  if (argc > 2)
    control_file = argv[2];
  if (argc > 3)
    time_quantum = atoi(argv[3]);

  sim_init();
  sim_run(plan_file, control_file);

  return 0;
}
