#include "cs.h"

int             server(int readfd, int writefd)
{

	char            buff[MAXBUFF+4];

	char            errmesg[256];

	int             n, fd;

	extern int      errno;


	 /* Read the filename from the IPC descriptor */ 

	if ((n = read(readfd, buff, MAXBUFF)) != MAXBUFF)
	{

		err_sys("Server: filename read error!");

	}
	if ((fd = open(buff, 0)) < 0)
	{


		/*
		 * Error. Format an error message and send it back to the
		 * client.
		*/
		sprintf(errmesg, ": can.t open, %s\n", sys_err_str());

		strcat(buff, errmesg);

		n = strlen(buff);


		if (write(writefd, buff, n) != n)
		{
			err_sys("Server: errmesg write error!");

		}
	} 
	else
	{


		/*
		 * Read the data from the file and write to the IPC
		 * descriptor.
		*/

		while ( (n = read(fd, buff, MAXBUFF)) >= 0)
		{


			
			fprintf(stderr,"s size=%d\n",n); 
			
			 ///////////transmit always the size
			
			if (write(writefd, buff, MAXBUFF+4) != MAXBUFF+4)
			{

				err_sys("Server: data write error!");

			}
			if (n==0) break;  //if zie was zero we are finished
		}
		if (n < 0)
		{

			err_sys("Server: read error!");

		}
	}
	fprintf(stderr,"server main loop ends \n\n\n");
	return 0;

}
