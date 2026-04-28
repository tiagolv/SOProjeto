CC = cc -Wall

OBJS = error.o mainfifoserv.o mainfifocli.o client.o server.o


all: server client

server: $(OBJS)
	cc -Wall -o server mainfifoserv.o server.o error.o

client: $(OBJS)
	cc -Wall -o client mainfifocli.o client.o error.o
	rm -f *.o	

S: server	
	./server	

C: client
	./client

clean:
	rm -f client server *.o
