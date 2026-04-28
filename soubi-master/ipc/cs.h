#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define err_sys(STR)    fprintf(stderr,STR)
#define err_sys2(STR,V) fprintf(stderr,STR,V)

#define MAXBUFF 1024

char *sys_err_str(void);

int client(int in , int out);
int server (int in , int out);



