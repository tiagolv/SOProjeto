#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define sz sizeof(int)
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666

int main()
{

    int max, r1, r2;
    //server
    int readfd, writefd;
    /* Create the FIFOs, then open them -one for reading and one for writing.*/
    umask(0);
    mknod(FIFO1, S_IFIFO | PERMS, 0);
    mknod(FIFO2, S_IFIFO | PERMS, 0);

    readfd = open(FIFO1, 0);
    writefd = open(FIFO2, 1);

    read(readfd, &max, sz);
    srand(time(NULL));
    r1 = 1 + rand() % max;
    r2 = 1 + rand() % max;
    write(writefd, &r1, sz);
    write(writefd, &r2, sz);
    return 0;
}