CC = cc -Wall

OBJS = error.o mainpipefork.o server.o client.o

s_pipe : $(OBJS) cs.h
	$(CC) -o s_pipe $(OBJS)

clean :
	rm s_pipe $(OBJS)
