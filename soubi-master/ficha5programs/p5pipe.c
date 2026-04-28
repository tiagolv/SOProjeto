#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#define sz sizeof(int)

int main()
{
	int p1[2],p2[2], pid;
	pipe(p1);
	pipe(p2);
	pid = fork();
	if (0==pid){
		int max,r1,r2;
		//cliente
		printf("Introduza o valor: ");
		scanf("%d",&max);
		write(p1[1],&max,sz);
		read(p2[0],&r1,sz);
		read(p2[0],&r2,sz);
		printf("%d %d\n",r1,r2);
	}else{
		int max,r1,r2;
		//server
		read(p1[0],&max,sz);
		srand(time(NULL));
		r1=1+rand()%max;
		r2=1+rand()%max;
		write(p2[1],&r1,sz);
		write(p2[1],&r2,sz);
	}
	return 0;
}