//Usando os meus Macros
//#include "semmaps.h"

// Usando apenas POSIX
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10  //numero de alunos /threads
#define K 3   //numero de garfos

#define PAUSA(A) {fflush(stdin);printf("Pausa %s\n",A);getchar();}

//uma pausa ativa a gastar CPU
#define pausa {double \
  indicez1;for(indicez1=0;indicez1<10000;indicez1=indicez1+0.1);}

// globais partilhadas
int numx = 0;  //numero de alunos a comer num dado momento 


void       *aluno(void *args);

int main(int argc, char *argv[])
{
	//identificadores dos threads
	pthread_t th[N];
	int  id[N];
	int i;

	for (i = 0; i < N; i++) {
		id[i] = i;
	}

	//PAUSA("Start: Iniciar press return ")
	
	for (i = 0; i < N; i++)
		pthread_create(&th[i], NULL, aluno, &id[i]);
	for (i = 0; i < N; i++)
		pthread_join(th[i], NULL);
	
	return 0;
}


void *aluno(void *args)
{
	int id,  //id do aluno 
            comer = 100;  //fazer o ciclo esperar/comer/beber 100 vezes

	id = *((int *) args);

	while ( comer-- > 0 ) {

		printf("Aluno %d a espera\n",id);pausa
		
		
		
		numx++;    //agarrar num garfo e comer a comida
		
		
		
		printf("Aluno %d a comer :  ****total %d a comer\n", id, numx);fflush(stdout);pausa;

		
		numx--;  //largar o garfo  e parar de comer a comido
		
		
		printf("Aluno %d a beber cerveja\n", id);fflush(stdout);pausa;
	}

	return NULL;
}

