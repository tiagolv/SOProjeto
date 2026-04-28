CC=cc


fome	: fome.c
	$(CC) -o fome fome.c -l pthread

jantar : filosofo.c
	$(CC) -o jantar filosofo.c -lpthread


ex1 : ex1.c
	$(CC) -DLINUX -o ex1 ex1.c -lpthread -lrt
ex1n : ex1.c
	$(CC) -DLINUX_POSIXNAMED -o ex1 ex1.c -lpthread -lrt
ex1dm: ex1.c
	$(CC) -DDARWIN_MACH -o ex1 ex1.c -lpthread 
ex1dn : ex1.c
	$(CC) -DDARWIN_POSIXNAMED -o ex1 ex1.c -lpthread 

jantarp : filosofo-allos.c
	$(CC) -DLINUX -o jantar filosofo-allos.c -lpthread -lrt
jantarn : filosofo.c
	$(CC) -DLINUX_POSIXNAMED -o jantar filosofo-allos.c -lpthread -lrt
jantardm : filosofo.c
	$(CC) -DDARWIN_MACH -o jantar filosofo-allos.c -lpthread 
jantardn : filosofo.c
	$(CC) -DDARWIN_POSIXNAMED -o jantar filosofo-allos.c -lpthread


clean :
	rm -rf fome ex1 jantar *~
