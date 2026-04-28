#include "cs.h"
#include "fifo.h"

int main()
{

	int             readfd, writefd;


	umask(0);


	if ((writefd = open(FIFO1, 1)) < 0)
	{			/* Open the FIFOs. We assume the server has
				 * already created them. */

		fprintf(stderr, "client: can't open write fifo: %s", FIFO1);

		return (-1);

	}
	if ((readfd = open(FIFO2, 0)) < 0)
	{

		fprintf(stderr, "client: can't open read fifo: %s", FIFO2);

		return (-1);

	}
	client(readfd, writefd);


	close(readfd);

	close(writefd);


	
	return (0);

}
