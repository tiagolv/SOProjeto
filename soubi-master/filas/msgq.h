#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define err_sys(STR) fprintf(stderr,STR)
#define err_sys2(STR,XXX) fprintf(stderr,STR,XXX)
#define err_dump(XXX) fprintf(stderr,XXX)
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
extern int errno;
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MKEY1 0x11
#define MKEY2 0x12
#define PERMS 0666

#define MAXMESGDATA 100

typedef struct { long int mesg_type; char mesg_data[MAXMESGDATA]; int mesg_len;  }  Mesg;

int server(int , int);
int client(int, int);

void mesg_send (int id, Mesg * mesgptr);
int mesg_recv(int id, Mesg *mesgptr);


/* help ..funcões da bash shell para manipular filas
ipcs
ipcrm
*/
