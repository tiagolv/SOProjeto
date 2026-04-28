#include "report.h"
#include "scheduler.h"
#include "queue.h"

static void print_pcb(PCB *p)
{
  printf("pid=%d ppid=%d prio=%d var=%d start=%d cpu=%d state=%d\n",
         p->pid, p->ppid, p->priority, p->var, p->start_time, p->cpu_time, p->state);
}

static void report_queue(queue_t *q, const char *title)
{
  int i;
  int idx;

  printf("%s\n", title);
  for (i = 0; i < q->count; i++)
  {
    idx = q->items[(q->head + i) % MAX_PROC];
    print_pcb(&pcb_table[idx]);
  }
}

void report_state(void)
{
  printf("TEMPO ACTUAL: %d\n", tempo);
  printf("ESCALONADOR: %s\n", scheduler_name(policy));

  printf("PROCESSO EM EXECUCAO:\n");
  if (running >= 0)
    print_pcb(&pcb_table[running]);
  else
    printf("(nenhum)\n");

  report_queue(&blocked_q, "PROCESSOS BLOQUEADOS:");
  report_queue(&ready_q, "PROCESSOS PRONTOS:");
  report_queue(&term_q, "PROCESSOS TERMINADOS:");
}

void report_global(void)
{
  int i;

  printf("ESTATISTICAS GLOBAIS\n");
  for (i = 0; i < MAX_PROC; i++)
  {
    if (pcb_table[i].used && pcb_table[i].state == ST_TERMINATED)
      print_pcb(&pcb_table[i]);
  }
}
