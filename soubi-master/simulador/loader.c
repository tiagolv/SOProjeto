#include "loader.h"

static int parse_instruction_line(const char *line, instruction *out)
{
  char op;
  int n;
  char nome[MAX_NAME];

  if (sscanf(line, " %c", &op) != 1)
    return -1;

  out->ins = op;
  out->n = 0;
  out->nome[0] = '\0';

  if (op == 'M' || op == 'A' || op == 'S' || op == 'C')
  {
    if (sscanf(line, " %c %d", &op, &n) != 2)
      return -1;
    out->n = n;
    return 0;
  }

  if (op == 'L')
  {
    if (sscanf(line, " %c %15s", &op, nome) != 2)
      return -1;
    strncpy(out->nome, nome, MAX_NAME - 1);
    out->nome[MAX_NAME - 1] = '\0';
    return 0;
  }

  if (op == 'B' || op == 'T')
    return 0;

  return -1;
}

int loader_read_program(const char *filename, instruction *buf, int max, int *out_count)
{
  FILE *fp;
  char line[128];
  int count = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    char alt[64];
    snprintf(alt, sizeof(alt), "programs/%s", filename);
    fp = fopen(alt, "r");
    if (fp == NULL)
      return -1;
  }

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    if (count >= max)
      break;
    if (line[0] == '#' || line[0] == '\n')
      continue;
    if (parse_instruction_line(line, &buf[count]) == 0)
      count++;
  }

  fclose(fp);
  *out_count = count;
  return 0;
}

int loader_read_plan(const char *filename)
{
  FILE *fp;
  char line[128];
  int count = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
    return -1;

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char nome[MAX_NAME];
    int arrival = 0;
    int priority = 0;
    int fields;

    if (line[0] == '#' || line[0] == '\n')
      continue;

    fields = sscanf(line, " %15s %d %d", nome, &arrival, &priority);
    if (fields >= 2 && count < MAX_PLAN)
    {
      strncpy(plan_list[count].nome, nome, MAX_NAME - 1);
      plan_list[count].nome[MAX_NAME - 1] = '\0';
      plan_list[count].arrival = arrival;
      plan_list[count].priority = (fields == 3) ? priority : 0;
      count++;
    }
  }

  fclose(fp);
  plan_count = count;
  return 0;
}

int loader_read_control(const char *filename)
{
  FILE *fp;
  char line[128];
  int count = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
    return -1;

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char cmd;

    if (line[0] == '#' || line[0] == '\n')
      continue;

    if (sscanf(line, " %c", &cmd) == 1 && count < MAX_CONTROL)
    {
      control_cmds[count] = cmd;
      count++;
    }
  }

  fclose(fp);
  control_count = count;
  return 0;
}
