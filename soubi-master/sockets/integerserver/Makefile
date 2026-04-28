SIO = ../socketio/socketio.o

all: client server
	ls

client : client-int.c ${SIO}
	cc -Wall -o client-int client-int.c ${SIO}

server : server-int.c ${SIO}
	cc -Wall -o server-int server-int.c ${SIO}

clean:
	rm -rf *.o *~ client-int server-int
	ls
