#include "../socketio/socketio.h"

int main(int argc, char **argv)
{
	int clientfd, port;
	char *host, buf[MAXLINE];

	if (argc != 3) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = atoi(argv[2]);

	clientfd = open_clientfd(host, port);
	CHECK(clientfd, "client socket file descriptor")

	while ( printf("Enter String: "), fgets(buf, MAXLINE, stdin) != NULL) {
		writen(clientfd, buf, strlen(buf));
		readline(clientfd, buf, MAXLINE);
		printf("Recieved:     %s", buf);
	}

	printf("Fechar socket\n");
	writen(clientfd, buf, 0);
	close(clientfd);
	exit(0);
}

