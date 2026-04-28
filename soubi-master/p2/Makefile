# Makefile for substituiting the high level standard library
#
# type 
# make main OR make mainstd or make test or male all (para compilar tudo)
#
# define the compiler as a variable
CC = cc -Wall

all : main mainstd test1

soio.o: soio.c soio.h
	$(CC) -c soio.c -o soio.o

main.o: main.c soio.h
	$(CC) -c main.c
	
mainstd.o: mainstd.c
	$(CC) -c mainstd.c

test1.o: test1.c soio.h
	$(CC) -c test1.c

main: main.o soio.o soio.h
	$(CC) -o main main.o soio.o

test1: test1.o soio.o soio.h
	$(CC) -o test1 test1.o soio.o

mainstd: mainstd.o 
	$(CC) -o mainstd mainstd.o 

#para remover todos os ficheiros executaveis e temporarios : type
#make clean

clean :
	rm -f *.o *~ main test1 mainstd

