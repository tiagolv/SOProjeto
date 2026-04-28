#include "semmaps.h"
#define N 20		//number of threads

SEM_T mutex;		//declaration of a binary semaphore for mutual exclusion
int x = 0;			//global  variable

void *f (void *args)
{
  SEM_WAIT (mutex);	//each thread adds one to a shared variable
  x = x + 1;
  SEM_POST (mutex);
}

int main (int argc, char *argv[])
{
  pthread_t th[N];
  int i;

  SEM_INIT (mutex, 0, 1);	//initialization of the binary semaphore.

  for (i = 0; i < N; i++)
    pthread_create (&th[i], NULL, f, NULL);
  for (i = 0; i < N; i++)
    pthread_join (th[i], NULL);
  printf("x = %d  (=%d)\n",x,N);
  return 0;
}

