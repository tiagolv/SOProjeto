#include "shell.h"
#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

char prompt[100];

int main()
{
  int len;
  char linha[1024]; /* um comando */
  char *args[64];   /* com um maximo de 64 argumentos */

  strcpy(prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf("%s", prompt);
    if (fgets(linha, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }
    len = strlen(linha);
    if (1 == len)
      continue; /* linha é apenas \n */
    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';
    int argc = parse(linha, args); /* particiona a string em argumentos */

    if (!builtin(argc, args))
      execute(argc, args); /* executa o comando */
  }
  return 0;
}

int builtin(int numArgs, char **args)
{
  if (strcmp(args[0], "sair") == 0)
  {
    exit(0);
    return 1;
  }
  if (strncmp(args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    return 1; /* funcionalidade embutida */
  }
  if (strlen(args[0]) > 4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0] + 4);
    return 1; // comando embutido
  }
  if (0 == strcmp(args[0], "quemsoueu"))
  {
    system("id");
    return 1;
  }
  if (0 == strcmp(args[0], "socp"))
  {
    FILE *fonte, *destino;
    fonte = fopen(args[2], "r");
    destino = fopen(args[1], "w");

    char aux = fgetc(fonte);
    while (aux != EOF)
    {
      fputc(aux, destino);
      aux = fgetc(fonte);
    }

    fclose(fonte);
    fclose(destino);

    return 1;
  }
  if (0 == strcmp(args[0], "obterinfo"))
  {
    printf("SoShell 2022 versaõ 1.0\n");
    return 1; // comando embutido
  }
  if (0 == strcmp(args[0], "cd"))
  {
    int err;
    if (NULL == args[1] || strcmp(args[1], "~") == 0)
      err = chdir(getenv("HOME"));
    else
      err = chdir(args[1]);
    if (err < 0)
      perror(args[1]);
    return 1;
  }

  if (0 == strcmp(args[0], "calc") && numArgs == 4)
  {
    calc(args[1], args[2], args[3]);
    return 1;
  }
  if (0 == strcmp(args[0], "bits") && numArgs == 4)
  {
    bits(args[1], args[2], args[3]);
    return 1;
  }
  if (0 == strcmp(args[0], "isjpeg") && numArgs == 2)
  {
    int fileDescriptor = open(args[1], O_RDONLY);
    if (isjpeg(fileDescriptor))
    {
      printf("O ficheiro é um jpeg\n");
    }
    else
    {
      printf("O ficheiro não é um jpeg\n");
    }
    close(fileDescriptor);

    return 1;
  }
  if (strcmp(args[0], "avisoTeste") == 0 && numArgs == 3)
  {
    aviso(args[1], atoi(args[2]));
    return 1;
  }
  if (strcmp(args[0], "aviso") == 0)
  {
    pthread_t th;
    aviso_t *ptr = (aviso_t *)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo = atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper, (void *)ptr);
    return 1;
  }
  if (strcmp(args[0], "maior") == 0 && numArgs == 3)
  {
    struct stat s1, s2;
    stat(args[1], &s1);
    stat(args[2], &s2);
    float sz1 = s1.st_size / 1024.0;
    float sz2 = s2.st_size / 1024.0;
    if (s1.st_size >= s2.st_size)
    {
      printf(" %s é maior %.lf kb\n", args[1], sz1);
    }
    else
    {
      printf(" %s é maior %.lf kb\n", args[2], sz2);
    }

    return 1;
  }
  if (strcmp(args[0], "setx") == 0 && numArgs == 2)
  {
    struct stat s;
    stat(args[1], &s);
    mode_t m = s.st_mode;
    m = m | S_IXUSR;
    chmod(args[1], m);

    return 1;
  }
  if (strcmp(args[0], "removerl") == 0 && numArgs == 2)
  {
    struct stat s;
    if (stat(args[1], &s) < 0)
    {
      perror(NULL);
      return 1;
    };
    mode_t m = s.st_mode;
    m = m & ~(S_IROTH | S_IRGRP);
    if (chmod(args[1], m) < 0)
      perror(NULL);

    return 1;
  }
  if (strcmp(args[0], "sols") == 0)
  {
    DIR *dp;
    struct dirent *dirp;
    if (args[1] != NULL && strcmp(args[1], "") != 0)
    {
      dp = opendir(args[1]);
    }
    else
    {
      dp = opendir("../soshell");
    }

    if (dp == NULL)
    {
      perror(NULL);
      return 1;
    }
    printf("inode name size \n");
    while ((dirp = readdir(dp)) != NULL)
    {
      struct stat s1;
      stat(dirp->d_name, &s1);
      printf("%lld %s size %ld\n", (long long)dirp->d_ino, dirp->d_name, s1.st_size);
      closedir(dp);
      return 1;
    }
  }
  if (strcmp(args[0], "tipo") == 0 && numArgs == 2)
  {
    struct stat s;
    if (stat(args[1], &s) < 0)
    {
      perror(NULL);
      return 1;
    }

    if (S_ISREG(s.st_mode))
    {
      printf("ficheiro regular\n");
    }
    else if (S_ISDIR(s.st_mode))
    {
      printf("Diretório\n");
    }
    else
    {
      printf("Outro tipo de arquivo\n");
    }
    return 1;
  }
  /* IMPORTANTE :
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}