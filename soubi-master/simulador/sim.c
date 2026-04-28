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
    process_create(plan_list[plan_index].nome, 0, plan_list[plan_index].priority);
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

void sim_run(const char *plan_file, const char *control_file)
{
  int i;

  if (loader_read_plan(plan_file) < 0)
  {
    printf("Nao foi possivel ler plan.txt\n");
    return;
  }
  if (loader_read_control(control_file) < 0)
  {
    printf("Nao foi possivel ler control.txt\n");
    return;
  }

  sim_check_arrivals();

  for (i = 0; i < control_count; i++)
  {
    char cmd = control_cmds[i];

    if (cmd == 'E')
      exec_quantum();
    else if (cmd == 'I')
      sim_interrupt_running();
    else if (cmd == 'D')
      scheduler_long();
    else if (cmd == 'R')
      report_state();
    else if (cmd == 'T')
      break;
  }

  report_global();
}
