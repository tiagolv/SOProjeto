#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

typedef struct { char msg[100] ; int tempo;} aviso_t;
typedef struct { char fonte[100]; char destino[100]; }copiar_t;

int parse(char *buf, char **args);

void execute(int argc, char **args);

int builtin(int argc, char **args);

void calc(char* value1, char *op, char *value2);

void bits(char* op1, char *opBin, char *op2);

int isjpeg(int fileDescriptor);

void aviso(char *mesg, int tempo);

void *avisowrapper(void *args);

int redirects(int numargs, char *args[]);

/* constantes que podem tornar uteis*/
#define BG 0
#define FG 1