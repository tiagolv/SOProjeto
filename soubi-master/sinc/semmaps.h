#ifndef _SEMMAPS
#define SEMMAPS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define LINUX
//#define LINUX_POSIXNAMED
//#define DARWIN_MACH
//#define DARWIN_POSIXNAMED

#ifdef LINUX
  #include <semaphore.h>
  #define SEM_T sem_t
  #define SEM_INIT(SEM,V,INITIAL) 	sem_init(&SEM, V, INITIAL);
  #define SEM_WAIT(SEM)             sem_wait(&SEM);
  #define SEM_POST(SEM)             sem_post(&SEM);
  #define  _REENTRANT
#endif

#ifdef LINUX_POSIXNAMED
#include <semaphore.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <errno.h>
/*
  notes
  tmpnam(NULL) will not return a correctly formed string name 
   has to start with /xyz
  note that this will create a kernel persistant semaphore in /dev/shm whose name is sem.xyz
   will need to reboot or sem_unlink to remove this
   However .. only get one semaphore..
*/
#define SEM_T sem_t *
#define SEM_INIT(SEM,V,INITIAL)    {char *sname="/tmp1"; \
	SEM = sem_open( sname , O_CREAT, S_IRUSR|S_IWUSR, INITIAL);\
	if (SEM==SEM_FAILED) printf("sem failed %d %s\n",errno,strerror(errno)); }
#define SEM_WAIT(SEM)               sem_wait(SEM);
#define SEM_POST(SEM)               sem_post(SEM);
#endif

#ifdef DARWIN_MACH
  #include <mach/mach_init.h>
  #include <mach/task.h>
  #include <mach/semaphore.h>
  #define  _REENTRANT
  #define SEM_T semaphore_t
  #define SEM_INIT(SEM,V,INITIAL)  semaphore_create(current_task(), &SEM, SYNC_POLICY_FIFO, INITIAL);
  #define SEM_WAIT(SEM)            semaphore_wait(SEM);
  #define SEM_POST(SEM)            semaphore_signal(SEM);
#endif

#ifdef DARWIN_POSIXNAMED
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <errno.h>
/* Notes
 sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int initialValue);
 tmpnam(NULL) this will create a semaphore with a unique name
 see man pages for details
  sem_open return an address but in <sys/semaphore.h> we have define SEM_FAILED -1  .. strange!
  so i put the typecast in below just to avoid seeing the warning
*/
#define SEM_T sem_t *
#define SEM_INIT(SEM,V,INITIAL)     {SEM = sem_open(  tmpnam(NULL), O_CREAT, S_IRUSR|S_IWUSR, INITIAL); \
												 if ((int)SEM==SEM_FAILED) printf("sem failed %d %s\n",errno,strerror(errno)); }
#define SEM_WAIT(SEM)               sem_wait(SEM);
#define SEM_POST(SEM)               sem_post(SEM);
#endif

#endif
 

