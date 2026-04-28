/*
 *  soio.h
 *
 *  Created by Paul Crocker on 3/11/07.
 *  Copyright 2007 UBI. All rights reserved.
 *
 */
/* soio.h */

#ifndef	_SOSTDIO_H_
#define	_SOSTDIO_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXBUFFSIZE	16 
#define EOF    		(-1)

typedef struct {  int fd;  char *buf; int index; int  size; } SOFILE;

SOFILE * sofopen( const char *nome, const char * mode);
int sofclose (SOFILE * fp);
int sofgetc  (SOFILE * fp);
int sofflush (SOFILE * fp);

#endif /* _SOSTDIO_H_ */


