#include "cs.h"
#include "fifo.h"

int main()
{

	int             readfd, writefd;


	/*
	 * Create the FIFOs, then open them - one for reading and one * for
	 * writing.
	*/

	umask(0);


	if ((mknod(FIFO1, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST))
	{

		fprintf(stderr, "can't create fifo: %s", FIFO1);

		return (-1);

	}
	if ((mknod(FIFO2, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST))
	{

		unlink(FIFO1);

		fprintf(stderr, "can't create fifo: %s", FIFO2);

		return (-1);

	}
	if ((readfd = open(FIFO1, 0)) < 0)
	{

		fprintf(stderr, "server: can't open read fifo: %s", FIFO1);

		return (-1);

	}
	if ((writefd = open(FIFO2, 1)) < 0)
	{

		fprintf(stderr, "server: can't open write fifo: %s", FIFO2);

		return (-1);

	}
	server(readfd, writefd);


	close(readfd);

	close(writefd);


	return (0);

}
