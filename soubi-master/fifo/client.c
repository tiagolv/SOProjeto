#include "cs.h"
int 
client(int readfd, int writefd)
{

	char   buff[MAXBUFF];

	int    n;


	/*
	 * Read the filename from the standard input, write it to the IPC
	 * descriptor
	*/

	fprintf(stderr, "Introduza nome do ficheiro a pedir ao server >");

	if (fgets(buff, MAXBUFF, stdin) == NULL) {
		err_sys("Client: filename read error!");
	}
	n = strlen(buff);

	if (buff[n - 1] == '\n') {
		buff[n - 1] = '\0';	/* ignore newline from fgets() */
	}
	if (write(writefd, buff, MAXBUFF) != MAXBUFF) {
		err_sys("Client: filename write error!");
	}
	/* Read the data from the IPC descriptor and write to standard output */

	while ((n = read(readfd, buff, MAXBUFF)) > 0) {
		if (write(1, buff, n) != n)	/* fd 1 = stdout */
			err_sys("Client: data write error!");

	}

	if (n < 0) {
		err_sys("Client: data read error!");
	}
	return 0;

}
