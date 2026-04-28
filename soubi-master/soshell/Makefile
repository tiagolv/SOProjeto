#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm -lpthread
OBS=main.o execute.o parse.o calc.o bits.o isjpeg.o redirects.o aviso.o

#Alvo por defeito é o primeiro
all :  soshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
calc.o : shell.h calc.c
	$(CC) $(FLAGS) calc.c
bits.o : shell.h bits.c
	$(CC) $(FLAGS) bits.c
isjpeg.o : shell.h isjpeg.c
	$(CC) $(FLAGS) isjpeg.c
aviso.o : shell.h aviso.c
	$(CC) $(FLAGS) aviso.c
redirects.o : shell.h redirects.c
	$(CC) $(FLAGS) redirects.c
soshell : $(OBS)
	$(CC)  -o soshell  $(OBS) $(LIBS)
clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
