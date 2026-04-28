#include "shell.h"

// redirects.c
// redirects tratamento dos simbolos por ordem inversa: i) 2> ii) > OU > iii) <
int redirects(int numargs, char *args[])
{
 // i tratar do redirect do 2>
    if ( numargs <3) return numargs; //Guard the following section

    if ( strcmp(args[numargs -2] , "2>") ==0) {
        int fd= creat ( args[numargs -1], 0666);
        if (fd<0) { perror( NULL ) ; exit (1) ; /*indicar um erro*/ }
        dup2(fd, STDERR_FILENO) ;
        close(fd);
        args[numargs -2]=NULL ;
        numargs = numargs -2 ;
 }
  
    if ( numargs <3) return numargs;

    if( strcmp(args[numargs-2], "SAIDA") == 0){
        int fd = creat ( args[numargs -1], 0666);
        if (fd<0) { perror( NULL ) ; exit (1) ; /*indicar um erro*/ }

        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[numargs -2]=NULL ;
        numargs = numargs - 2;
    }
 //ii tratar do redirect do >
 //verificar casos de (>) ou append (>>)
 if ( numargs <3) return numargs;
 if( strcmp(args[numargs-2], ">>") == 0){
        int fd = open(args[numargs-1], 0666 | O_APPEND, 0);
        if (fd<0) { perror( NULL ) ; exit (1) ; /*indicar um erro*/ }

        dup2(fd, STDOUT_FILENO);

        close(fd);
        args[numargs -2]=NULL ;
        numargs = numargs -2 ;
    }
 //tratar do > creat ou >> open O_WRONLY | O_APPEND

 if ( numargs <3) return numargs;

 if( strcmp(args[numargs - 2], "ENTRADA") == 0){
    
    int fd = open(args[numargs-1], 0666, 0);
    if (fd<0) { perror( NULL ) ; exit (1) ; /*indicar um erro*/}

    dup2(fd, STDIN_FILENO) ;
    close(fd);
    args[numargs -2]=NULL ;
    numargs = numargs -2 ;
    
 }

 // iii tratar do < open O_RDONLY
 return numargs; //devolver o numero de argumentos a passar para execvp
}