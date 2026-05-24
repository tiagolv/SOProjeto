#include "sim.h"
#include "queue.h"
#include "memory.h"
#include "loader.h"
#include "process.h"
#include "scheduler.h"
#include "exec.h"
#include "report.h"

instruction memory[MAX_MEMORY];
PCB pcb_table[MAX_PROC];
int pcb_count = 0;
int next_pid = 1;
int tempo = 0;
int running = -1;
int time_quantum = DEFAULT_QUANTUM;
sched_policy policy = SCHED_FCFS;
queue_t ready_q;
queue_t blocked_q;
queue_t term_q;
plan_entry plan_list[MAX_PLAN];
int plan_count = 0;
char control_cmds[MAX_CONTROL];
int control_count = 0;

static int plan_index = 0;

void sim_init(void)
{
  int i;

  memset(pcb_table, 0, sizeof(pcb_table));
  memset(plan_list, 0, sizeof(plan_list));
  memset(control_cmds, 0, sizeof(control_cmds));
  queue_init(&ready_q);
  queue_init(&blocked_q);
  queue_init(&term_q);
  mem_init();

  pcb_count = 0;
  next_pid = 1;
  tempo = 0;
  running = -1;
  policy = SCHED_FCFS;
  plan_index = 0;

  srand((unsigned)time(NULL));

  for (i = 0; i < MAX_PROC; i++)
    pcb_table[i].used = 0;
}

void sim_check_arrivals(void)
{
  while (plan_index < plan_count && plan_list[plan_index].arrival <= tempo)
  {
    int idx = process_create(plan_list[plan_index].nome, 0, plan_list[plan_index].priority);
    if (idx >= 0)
    {
      pcb_table[idx].period   = plan_list[plan_index].period;
      pcb_table[idx].deadline = plan_list[plan_index].deadline;
    }
    plan_index++;
  }
}

void sim_tick(void)
{
  tempo++;
  sim_check_arrivals();
}

void sim_interrupt_running(void)
{
  if (running < 0)
    return;

  process_block(running);
  running = -1;
}

static int plan_cmp(const void *a, const void *b)
{
  return ((plan_entry *)a)->arrival - ((plan_entry *)b)->arrival;
}

static void dispatch(char cmd)
{
  if (cmd == 'E')      exec_quantum();
  else if (cmd == 'I') sim_interrupt_running();
  else if (cmd == 'D') scheduler_long();
  else if (cmd == 'R') report_state();
}

void sim_run(const char *plan_file, const char *control_file)
{
  int i;
  int use_stdin;

  if (loader_read_plan(plan_file) < 0)
  {
    printf("Nao foi possivel ler %s\n", plan_file);
    return;
  }

  /* guarantee arrivals are processed in order regardless of plan.txt order */
  qsort(plan_list, plan_count, sizeof(plan_entry), plan_cmp);

  sim_check_arrivals();

  /* use stdin if no control file, "-" is given, or the file cannot be opened */
  use_stdin = (control_file == NULL ||
               strcmp(control_file, "-") == 0 ||
               loader_read_control(control_file) < 0);

  if (use_stdin)
  {
    char line[32];
    char cmd;
    printf("Modo interativo. Comandos: E I D R T\n");
    printf("> ");
    fflush(stdout);
    while (fgets(line, sizeof(line), stdin) != NULL)
    {
      if (sscanf(line, " %c", &cmd) != 1)
      {
        printf("> ");
        fflush(stdout);
        continue;
      }
      if (cmd == 'T')
        break;
      dispatch(cmd);
      printf("> ");
      fflush(stdout);
    }
  }
  else
  {
    for (i = 0; i < control_count; i++)
    {
      if (control_cmds[i] == 'T')
        break;
      dispatch(control_cmds[i]);
    }
  }

  report_global();
}
