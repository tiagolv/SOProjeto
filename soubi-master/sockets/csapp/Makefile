SIO = ../socketio/socketio.o

all: client server
	ls

client : echo-cli.c ${SIO}
	cc -Wall -o echo-cli echo-cli.c ${SIO}

server : echo-ser.c ${SIO}
	cc -Wall -o echo-ser echo-ser.c ${SIO}

clean:
	rm -rf *.o echo-ser echo-cli *~
	ls
