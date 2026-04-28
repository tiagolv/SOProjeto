#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
extern int errno;
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <time.h>

#define MKEY1 0x11
#define MKEY2 0x12
#define PERMS 0666

#define MAXMESGDATA 4  //sizeof an integer

typedef struct
{
  long int mesg_type;
  int mesg_data[MAXMESGDATA];
  int mesg_len;
} Mesg;

void mesg_send(int id, Mesg *mesgptr);
int mesg_recv(int id, Mesg *mesgptr);

/* funces uteis da bash shell para manipular e gerir filas
ipcs
ipcrm
*/
