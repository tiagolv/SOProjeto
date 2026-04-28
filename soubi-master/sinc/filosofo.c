/*
	Jantar dos Filosofos
	Version : POSIX
	Author: Paul Crocker
	Notes : Este programa deverá bloquear (deadlock)
*/
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#define N 5			//numero de filosofos

#define PAUSA(A) {fflush(stdin);printf("Pausa %s\n",A);getchar();}
#define pausa {double indicez1;for(indicez1=0;indicez1<10;indicez1=indicez1+0.01);}

sem_t pau[N];

void *filosofo (void *args);

int main (int argc, char *argv[])
{
  pthread_t th[N];
  int i, id[N];
  for (i = 0; i < N; i++)
    {
      id[i] = i;
      sem_init (&pau[i], 0, 1);
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

      sem_wait(&pau[esq]);
      pausa; /*este ponto é critico */
      sem_wait(&pau[dir]);

      printf ("Estou a comer thread %d %d\n", id, comer); pausa;
      comer = comer - 1; pausa;
      
      sem_post (&pau[esq]);
      sem_post (&pau[dir]);
    }

  return (NULL);
}
