#include "cs.h"

/*Todos as mensagens de erro estão escritos no candelç de stderr */

int server(int readfd, int writefd)
{

	char            buff[MAXBUFF];

	char            errmesg[256];

	int             n, fd;

	extern int      errno;


	/* Read the filename from the IPC pipe file descriptor */

	if ((n = read(readfd, buff, MAXBUFF)) != MAXBUFF)
		err_sys("Server: filename read error!");



	if ( (fd = open(buff,O_RDONLY) ) < 0 )
	{
		/*
		 * Erro na Abertura do ficheiro.
		 * Format an error message and send it back to the client.
		 */

		sprintf(errmesg, ": can.t open, %s\n", sys_err_str());
		strcat(buff, errmesg);

		n = strlen(buff);

		if (write(writefd, buff, n) != n)
			err_sys("Server: errmesg write error!");

	} else
	{

		/*
		 * Read the data from the file and write to the IPC
		 * descriptor.
		 * Read and Write Blocks of size MAXBUFF
		 */

		while ((n = read(fd, buff, MAXBUFF)) > 0)
			if (write(writefd, buff, n) != n)
				err_sys("Server: data write error!");

		if (n < 0)
			err_sys("Server: read error!");

	}

	return 0;
}
