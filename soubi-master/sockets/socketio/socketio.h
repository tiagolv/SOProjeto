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
#include <netinet/in.h>
#include <arpa/inet.h>

#define CHECK(S,Q) serr(S,Q);

typedef struct sockaddr SA;

#define LISTENQ 10

#define MAXLINE 1024

//robust I/O operations for sockets 
ssize_t readn (int fd, void *buf, size_t count);
ssize_t writen (int fd, const void *buf, size_t count);

//buffered read a line from a socket
ssize_t readline (int fd, void *buf, size_t maxlen);

//Open sockets and return file descriptors in a nice way
int open_listenfd(int port);
int open_clientfd(char *hostname, int port);

//error checking
char * serr(int S, char *Q);
