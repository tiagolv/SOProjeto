#include "bancos.h"

//escolhe um nome para o tipo de dados

typedef struct
{
  int idAtm;
  int idCliente;
  float valor;
} ..

//Max numero de clientes e threads
#define MAXCLI  20
#define MAXT 10

 /* variaveis partilhadas pelos threads */
int NT;
int NC;
float saldos[MAXCLI];
int cnt;

void *relatorio  (void *args);
void *multibanco (void *args);

int main (int argc, char *argv[])
{
  int i;
  pthread_t rel, atm[MAXT];

  printf("\n\nIntroduza o numero de ATM's (ate 10) e numero de clientes (ate 20):  ");
  scanf ("%d%d", &NT, &NC);

  printf ("Data in.bin. Voce Escolheu:  Threads= %d Clientes=%d\n\n", NT, NC);
  getchar(); //engolir /n

  //Initializar os saldos dos clientes
  for (i = 0; i < NC; i++)
    saldos[i] = 0.0;

  //Initializar um contador para travar thread do relatorio
  cnt = -NT;

  pthread_create (&rel, NULL, relatorio, NULL);

  //criar threads multibanco .. passar argumento 

  for (i = 0; i < NT; i++)
    {
       ....
      pthread_create (&atm[i], NULL, multibanco, ............  );
    }



   //terminar esta thread 

   return 0;
}

void *multibanco (void *args)
{
  int id = *(int *) args;

  //codigo

  return NULL;
}

void *relatorio(void *args)
{

  //codigo

  return NULL;
}
