#include "shell.h"

int containsPipe (int numArgs, char **args)
{
  int index;
  for (index = 0; index < numArgs; index++)
  if (args[index][0] == '|'){
    return index;
  }
 return -1;
}



int ultimo ( int *numargs, char **args ){

  if (args[*numargs-1][0]=='&') {
    *numargs=*numargs-1;
    args[*numargs]=NULL ;
  return BG;
  }
  return FG; /*return FG ou BG definidos no shell.h */
}


void execute (int num_args, char **args)
{
  int pid, status;
  int code = ultimo( &num_args , args);

  if ((pid = fork ()) < 0)
    { /* cria um processo progenito */
      perror ("forks");/* NOTE: perror() produz uma pequema mensagem de erro para o stream */
      exit (1);/* estandardizado de erros que descreve o ultimo erro encontrado */
               /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

  if (pid == 0)
    {
      if (strstr(args[0], "/") != NULL) {
        if (execv(args[0], args) == -1) {perror("soshell");}
        exit (1);
      }

      int index_of_pipe = containsPipe(num_args, args);
    
      if(index_of_pipe == -1){
      num_args = redirects(num_args, args);
      if(num_args == -1){exit(1);}
      
      execvp (*args, args);
      perror (*args);
      exit (1);
    }

    else{
    
      int pipefd[2];

      if(pipe(pipefd) == -1){
        perror(NULL);
        exit(1);
      }
      args[index_of_pipe] = NULL; 

      if(fork() == 0){

            dup2(pipefd[1], STDOUT_FILENO);

            close(pipefd[0]);
            close(pipefd[1]);

            if(redirects(index_of_pipe, args) == -1){exit(1);}

            execvp(args[0], args);

      }
      else{
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            close(pipefd[0]);
            num_args = num_args - index_of_pipe - 1;
            args = args + index_of_pipe + 1;
            if(redirects(num_args, args) == -1){exit(1);}
            execvp(args[0], args);
      }
    }                      
    }
    if( FG == code) while (wait(&status) != pid)
    /*spin fazer nada */ ;
  return;
}