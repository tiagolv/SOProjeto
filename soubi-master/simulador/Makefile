# Makefile for process scheduler simulator

CC = cc -Wall

OBJS = main.o sim.o queue.o memory.o loader.o scheduler.o process.o exec.o report.o

all: simulador

main.o: main.c sim.h
	$(CC) -c main.c

sim.o: sim.c sim.h queue.h loader.h process.h scheduler.h exec.h report.h
	$(CC) -c sim.c

queue.o: queue.c queue.h sim.h
	$(CC) -c queue.c

memory.o: memory.c memory.h loader.h sim.h
	$(CC) -c memory.c

loader.o: loader.c loader.h sim.h
	$(CC) -c loader.c

scheduler.o: scheduler.c scheduler.h queue.h sim.h
	$(CC) -c scheduler.c

process.o: process.c process.h memory.h queue.h sim.h
	$(CC) -c process.c

exec.o: exec.c exec.h scheduler.h process.h sim.h
	$(CC) -c exec.c

report.o: report.c report.h scheduler.h sim.h
	$(CC) -c report.c

simulador: $(OBJS)
	$(CC) -o simulador $(OBJS)

clean limpar:
	rm -f simulador *.o
