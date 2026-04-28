/*
** client.c - a stream socket client demo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#define PORT 3490		// the port client will be connecting to

#define MAXINTS 100

size_t readn (int fd, void *buf, size_t count);
size_t writen (int fd, const void *buf, size_t count);

int main (int argc, char *argv[])
{
  int sockfd, numbytes;
  int i, N, buf[MAXINTS];
  struct hostent *he;
  struct sockaddr_in their_addr;	// connector’s address information
  if (argc != 3)
    {
      fprintf (stderr, "usage: client hostname Numero\n");
      exit (1);
    }

  he = gethostbyname (argv[1]);	// get the host info
  N = atoi (argv[2]);
  if (N > MAXINTS)
    exit (1);
  else
    printf ("Pedido %d ints\n", N);

  sockfd = socket (AF_INET, SOCK_STREAM, 0);


  their_addr.sin_family = AF_INET;	// host byte order

  their_addr.sin_port = htons (PORT);	// short, network byte order
  their_addr.sin_addr = *((struct in_addr *) he->h_addr);
  memset (&(their_addr.sin_zero), '\0', 8);	// zero the rest of the struct
  connect (sockfd, (struct sockaddr *) &their_addr, sizeof (struct sockaddr));

  numbytes = writen (sockfd, &N, sizeof (int));

  if (numbytes != sizeof (int))
    {
      fprintf (stderr, "send error\n");
      exit (1);
    }

  numbytes = readn (sockfd, &buf[0], sizeof (int) * N);

  printf ("Received from server: %d bytes  == %d ints\n", numbytes,
	  numbytes / sizeof (int));
  for (i = 0; i < N; i++)
    printf ("%3d ", buf[i]);
  printf ("\n");

  close (sockfd);
  return 0;
}
