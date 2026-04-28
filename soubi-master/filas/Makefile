CFLAGS = -Wall 

OBJSS=mainserver.o subserver.o mesg.o
OBJSC=maincliente.o subcliente.o mesg.o

all : cliente server

server: $(OBJSS) msgq.h
	cc -o server $(OBJSS)
cliente: $(OBJSC) msgq.h
	cc -o cliente $(OBJSC)

clean:
	rm -f *.o server cliente
