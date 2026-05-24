#include "report.h"
#include "scheduler.h"
#include "queue.h"

static void print_pcb(PCB *p)
{
  printf("  [%s] pid=%d ppid=%d prio=%d var=%d start_t=%d cpu=%d",
         p->nome, p->pid, p->ppid, p->priority, p->var, p->start_time, p->cpu_time);
  if (p->state == ST_TERMINATED)
    printf(" end_t=%d turnaround=%d", p->end_time, p->end_time - p->start_time);
  if (p->period > 0)
    printf(" period=%d deadline=%d", p->period, p->deadline);
  printf("\n");
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
  int count = 0;
  int total_turnaround = 0;
  int total_cpu = 0;

  printf("\n=== ESTATISTICAS GLOBAIS (tempo=%d, escalonador=%s) ===\n",
         tempo, scheduler_name(policy));
  printf("PROCESSOS TERMINADOS:\n");
  for (i = 0; i < MAX_PROC; i++)
  {
    if (pcb_table[i].used && pcb_table[i].state == ST_TERMINATED)
    {
      print_pcb(&pcb_table[i]);
      total_turnaround += pcb_table[i].end_time - pcb_table[i].start_time;
      total_cpu += pcb_table[i].cpu_time;
      count++;
    }
  }
  if (count > 0)
    printf("Media turnaround=%.1f  Media cpu=%.1f  Processos=%d\n",
           (double)total_turnaround / count, (double)total_cpu / count, count);
}
