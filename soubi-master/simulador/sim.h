#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMORY 1000
#define MAX_PROC 50
#define MAX_NAME 16
#define MAX_PLAN 100
#define MAX_CONTROL 200

#define DEFAULT_QUANTUM 4

typedef enum
{
  ST_READY = 0,
  ST_RUNNING = 1,
  ST_BLOCKED = 2,
  ST_TERMINATED = 3
} proc_state;

typedef enum
{
  SCHED_FCFS = 0,
  SCHED_PRIO = 1,
  SCHED_SJF = 2,
  SCHED_RM = 3,
  SCHED_EDF = 4
} sched_policy;

typedef struct
{
  char ins;
  int n;
  char nome[MAX_NAME];
} instruction;

typedef struct
{
  int used;
  int pid;
  int ppid;
  char nome[MAX_NAME];
  int start;
  int size;
  int pc;
  int var;
  int priority;
  int start_time;
  int cpu_time;
  int end_time;
  int deadline;
  int period;
  proc_state state;
} PCB;

typedef struct
{
  int items[MAX_PROC];
  int head;
  int tail;
  int count;
} queue_t;

typedef struct
{
  char nome[MAX_NAME];
  int arrival;
  int priority;
} plan_entry;

extern instruction memory[MAX_MEMORY];
extern PCB pcb_table[MAX_PROC];
extern int pcb_count;
extern int next_pid;
extern int tempo;
extern int running;
extern int time_quantum;
extern sched_policy policy;
extern queue_t ready_q;
extern queue_t blocked_q;
extern queue_t term_q;
extern plan_entry plan_list[MAX_PLAN];
extern int plan_count;
extern char control_cmds[MAX_CONTROL];
extern int control_count;

void sim_init(void);
void sim_run(const char *plan_file, const char *control_file);
void sim_tick(void);
void sim_check_arrivals(void);
void sim_interrupt_running(void);

#endif
