#define sz sizeof(int)
#include "mesgs.h"
int main ()
{
  int max, r1, r2;

  //server
  int readid, writeid;
  Mesg mesg;

  /* Create the message queues, if required. */
  readid = msgget (MKEY1, PERMS | IPC_CREAT);
  writeid = msgget (MKEY2, PERMS | IPC_CREAT);
 
  mesg.mesg_type = 1L;
  mesg_recv (readid, &mesg);
  memcpy (&max, mesg.mesg_data, sz);
  
  srand (time (NULL));
  r1 = 1 + rand () % max;
  r2 = 1 + rand () % max;

  memcpy (mesg.mesg_data, &r1, sz);
  mesg.mesg_len = sz;
  mesg_send (writeid, &mesg);

  mesg.mesg_type = 2L;		//client will not get this message
  mesg.mesg_type = 1L;		//client will get this message
  r1 = -100;
  memcpy (mesg.mesg_data, &r1, sz);
  mesg.mesg_len = sz;
  mesg_send (writeid, &mesg);
  

  mesg.mesg_type = 1L;
  memcpy (mesg.mesg_data, &r2, sz);
  mesg.mesg_len = sz;
  mesg_send (writeid, &mesg);

  return 0;
}
