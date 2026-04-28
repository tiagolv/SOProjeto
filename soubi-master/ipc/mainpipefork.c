/*
  IPC with pipes
  Author: W.Stevens
  Modififcations. Paul Crocker
*/

#include "cs.h"

int    main()
{
	int childpid, pipe1[2], pipe2[2];

	if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
		err_sys("Can.t create pipes !\n");

	if ((childpid = fork()) < 0)
	{
		err_sys("can.t fork !\n");
	} 
        else if (childpid > 0)/* parent */
	{
		close(pipe1[0]); //fechamos as partes do pipe que não precisamos
		close(pipe2[1]); //não é necessário mas é um boa pratica
	
		client(pipe2[0], pipe1[1]);
	
		/* wait for child to finish */
		while (wait((int *) 0) != childpid)
			;

		close(pipe1[1]);
		close(pipe2[0]);
		
		exit(0);
	} else
	{

		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0], pipe2[1]);

		close(pipe1[0]);
		close(pipe2[1]);

		exit(0);
	}
	return 0;
}
