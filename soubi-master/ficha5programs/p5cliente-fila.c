
#define sz sizeof(int)
#include "mesgs.h"

int main()
{
    int max, r1, r2;
    //cliente
    int readid, writeid;
    Mesg mesg;

    /*
	 * Open the message queues.  The server must have already created them.
	 */

    writeid = msgget(MKEY1, 0);
    readid = msgget(MKEY2, 0);

    printf("Introduza o valor: ");
    scanf("%d", &max);

    memcpy( mesg.mesg_data, &max, sz);
	mesg.mesg_len = sz; 
	mesg.mesg_type = 1L;
	mesg_send(writeid, &mesg);

    mesg_recv(readid, &mesg); memcpy(  &r1, mesg.mesg_data, sz);

    mesg_recv(readid, &mesg); memcpy(  &r2, mesg.mesg_data, sz);

    printf("%d %d\n", r1, r2);

    /* Delete the FIFOs, now that we're finished */
    msgctl(readid, IPC_RMID, (struct msqid_ds *)0);
    msgctl(writeid, IPC_RMID, (struct msqid_ds *)0);

    return 0;
}