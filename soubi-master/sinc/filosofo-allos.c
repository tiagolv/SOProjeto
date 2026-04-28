/*
	Jantar dos Filosofos
	Version : POSIX ou MACOS
        4 types of semaphores may be chosen (see semmaps.h)
        use -DLINUX for standard Linux Posix threads
        Also LINUX_POSIXNAMED DARWIN_MACH DARWIN_POSIXNAMED
	Author: Paul Crocker
	Notes : Este programa deverá bloquear (deadlock)
*/

#include "semmaps.h"
#include <pthread.h>
#define N 5			//numero de filosofos

#define PAUSA(A) {fflush(stdin);printf("Pausa %s\n",A);getchar();}
#define pausa {double indicez1;for(indicez1=0;indicez1<10;indicez1=indicez1+0.01);}

SEM_T pau[N];

void *filosofo (void *args);

int main (int argc, char *argv[])
{
  pthread_t th[N];
  int i, id[N];
  for (i = 0; i < N; i++)
    {
      id[i] = i;
      SEM_INIT (pau[i], 0, 1);
    }
  PAUSA ("Start: Iniciar press return ");

  for (i = 0; i < N; i++)
    pthread_create (&th[i], NULL, filosofo, &id[i]);
  for (i = 0; i < N; i++)
    pthread_join (th[i], NULL);
  return 0;
}

void * filosofo (void *args)
{
  int id, esq, dir, comer = 10000;
  id = *((int *) args);

  esq = id;
  dir = (id + 1) % N;

  while (comer > 0)
    {
      printf ("Estou a pensar thread %d %d\n", id, comer);
      SEM_WAIT (pau[esq]);
      pausa;
      SEM_WAIT (pau[dir]);
  
      printf ("Estou a comer thread %d %d\n", id, comer);
    
      comer = comer - 1;
     
      SEM_POST (pau[esq]);
      SEM_POST (pau[dir]);
    }

  return (NULL);
}
