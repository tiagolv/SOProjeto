/*
 *  soio.c
 *
 *  Created by Paul Crocker on 3/11/07.
 *  Copyright 2007 UBI. All rights reserved.
 *
 */
#include "soio.h"

SOFILE *sofopen (const char *nome, const char *mode)
{
  SOFILE *novo = NULL;
  int fd;

  if (mode[0] == 'r')
    fd = open (nome, O_RDONLY, 0);
  else
    exit (1);			//agora apenas para leitura !

  if (-1 == fd)
    return NULL;		//caso erro

  char fdc ='0'+fd;  //ok if fd<=9
  write(2,"FD ",3); write(2,&fdc,1);  write(2,"\n",1);

  novo = (SOFILE *) malloc (sizeof (SOFILE));
  novo->buf = (char *) malloc (MAXBUFFSIZE);
  novo->fd = fd;
  novo->index = 0;
  novo->size = 0;
  return novo;
}

//Funções não implementadas

int sofclose (SOFILE * fp)
{
  return 0;
}

int sofgetc (SOFILE * fp)
{				/*substituir este codigo */
  int x[] = { 'x', 'o', 'l', 'a', '\n', -1 };
  static int i = 0;
  return x[i++];
}

int sofflush (SOFILE * fp)
{
  return 0;
}

