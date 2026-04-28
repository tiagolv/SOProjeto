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

    int
    main()
{
    int max, r1, r2;
    //cliente
    int readfd, writefd;
    umask(0);
    /* Open the FIFOs.  We assume the server has already created them. */
    writefd = open(FIFO1, 1);
    readfd = open(FIFO2, 0);
   
    printf("Introduza o valor: ");
    scanf("%d", &max);
    write(writefd, &max, sz);
    read(readfd, &r1, sz);
    read(readfd, &r2, sz);
    printf("%d %d\n", r1, r2);

    /* Delete the FIFOs, now that we're finished */
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}