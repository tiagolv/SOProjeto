#include "socketio.h"

ssize_t readn (int fd, void *buf, size_t count)
{

	size_t nleft = count;
	ssize_t nread;
	void *ptr = buf;		//char to void

	while (nleft > 0)
	{
		if ((nread = read (fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return -1;		/* errno set by read() */
		}

		else if (nread == 0)

			break;			/* EOF */

		nleft -= nread;
		ptr += nread;
	}

	return (count - nleft);	/* return >= 0 */
}

ssize_t writen (int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nwritten;
	const void *ptr = buf;	//char to void paulc

	while (nleft > 0)
	{
		if ((nwritten = write (fd, ptr, nleft)) <= 0)
		{
			if (errno == EINTR)
				nwritten = 0;	/* and call write() again */
			else
				return -1;		/* errorno set by write() */
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return count;
}

/*
  O coidio seguinte e para leruma linha
   Utilizamos uma função static chamado my_read para fazer buffering
*/

/* 
  Function returns
   -1 error
    0 no data read
    1  data read
*/

static ssize_t my_read (int fd, char *ptr)
{
	static int   read_cnt = 0;

//note the buffer read_buf is static and so is read_ptr the position in the buffer
	static char *read_ptr, read_buf[MAXLINE];

	if (read_cnt <= 0)
	{
again:
		if ((read_cnt = read (fd, read_buf, sizeof (read_buf))) < 0)
		{
			if (errno == EINTR)
				goto again;
			return -1;
		}
		else if (read_cnt == 0)
			return 0;
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}

/* esta função tem que ler uma linha de texto
   uma linha de texto é até se encontre um /n ou ate MAXLEN é encontrado
*/

ssize_t readline (int fd, void *buf, size_t maxlen)
{
	int n, rc;
	char c, *ptr = buf;

	for (n = 1; n < maxlen; n++)
	{				/* notice that loop starts at 1 */
		if ((rc = my_read (fd, &c)) == 1)
		{
			*ptr++ = c;
			if (c == '\n')
				break;		/* newline is stored, like fgets() */
		}
		else if (rc == 0)
		{
			if (n == 1)
				return 0;		/* EOF, no data read --> so readline retruns zero*/
			else
				break;		   /* EOF, some data was read  --> so break the for cycle and return a line of n length*/
		}
		else
			return -1;		/* error, errno set by read() */
	}
	*ptr = 0;			/* null terminate like fgets() */
	return n;
}

/*
   Cliente
	Dado um hostname e porta abrir um socket para ligar
*/
int open_clientfd(char *hostname, int port)
{
	int err,clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;

	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(clientfd,"client socket file descriptor");

	/* fill in the server’s IP address and port */
	hp = gethostbyname(hostname);
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr,(char *)&serveraddr.sin_addr.s_addr, hp->h_length);
	serveraddr.sin_port = htons(port);
	/* establish a connection with the server */
	err=connect(clientfd, (SA *) &serveraddr, sizeof(serveraddr));
	CHECK(err,"connect function");

	return clientfd;
}

/*
	Server:
   Dado uma porta abrir um socket para escutar na porta e aceitar ligações
*/
int open_listenfd(int port)
{
	int listenfd;
	int optval;
	int err;
	struct sockaddr_in serveraddr;

	/* create a socket descriptor */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK(listenfd,"listen file descriptor");

	/* eliminates "Address already in use" error from bind. */
	optval = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));

	/* listenfd will be an endpoint for all requests to port
	on any IP address for this host */
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);

	err=bind(listenfd, (const SA *)&serveraddr, sizeof(serveraddr));
	CHECK(err,"bind function");

	/* make it a listening socket ready to accept connection requests */
	err=listen(listenfd, LISTENQ);
	CHECK(err,"listen function");

	return listenfd;
}

char * serr(int S, char *Q)
{
	if (S<0){
		fprintf(stderr, "Err on %s=%d %s\n",Q,S,strerror(errno)); 
		exit(1); 
	} 
	else {
		fprintf(stderr, "Opened %s on %d\n",Q,S);}
}
