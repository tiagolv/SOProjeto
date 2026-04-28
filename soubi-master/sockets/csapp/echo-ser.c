#include "../socketio/socketio.h"
#include <netdb.h>

//listenfd --> listen file descriptor     : server socket listens 
//connfd   --> connection file descriptor : after accepting connection new socket connection socket is created


void echo(int connfd);

int main(int argc, char **argv)
{
	
	char hostClient[NI_MAXHOST];

	int listenfd, connfd, port;
	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof(clientaddr);

	char *haddrp="";
   	
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]);

	listenfd = open_listenfd(port);
	CHECK(listenfd,"listen socket file descriptor");
	
	while (1) {
		printf("Server waiting for a connection: \n");
		connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
		CHECK(connfd,"Connection Socket file descriptor");

		getnameinfo((const struct sockaddr*)&clientaddr,clientlen, hostClient,sizeof(hostClient), NULL, 0, 0);
		haddrp = inet_ntoa(clientaddr.sin_addr);
	
		printf("server connected to %s (%s)\n", hostClient, haddrp);

		echo(connfd);

		printf("server dis-connected from %s (%s)\n", hostClient, haddrp);
		close(connfd);
	}
}

void echo(int connfd)
{
	size_t n;
	char buf[MAXLINE];

	while((n = readline(connfd, buf, MAXLINE)) != 0) {
		printf("server received %d bytes\n", n);
		writen(connfd, buf, n);
	}
}

