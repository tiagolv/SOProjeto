/* 
 C Program to Copy a File using high level buffered IO
*/
#include <stdio.h>
#include <time.h>
int main (int argc, char **argv)
{
  clock_t inicio, fim;
  float tempoUsado;
  FILE *fp1, *fp2;
  int ch;
  if ((fp1 = fopen (argv[1], "r")) == NULL)
    {
      fprintf (stderr, "\nFile cannot be opened for reading");
      return 1;
    }
  if ((fp2 = fopen (argv[2], "w")) == NULL)
    {
      fprintf (stderr, "\nFile cannot be opened for Writing");
      return 1;
    }

  inicio = clock ();

  while ((ch = fgetc (fp1)) != EOF)
    {
      fputc (ch, fp2);		//copying file byte  by byte
    }
  fim = clock ();
  tempoUsado = (float) (fim - inicio) / (float) CLOCKS_PER_SEC;
  fprintf (stderr, "Tempo %f\n", tempoUsado);
  return 0;
}
