Exercicio para mostrar a diferenca entre uma 
biblioteca padrao (o standard input/output library) 
e as funções de baixo-nivel - as chamadas ao sistema.

Este exemplo mostre como uma biblioteca padrão poderá 
oferecer funcionalidades como "buffering"  e "optimização" 

cc -Wall main  main.c soio.c  
cc -Wall test1 test1.c soio.c

ou usando make
make main
make 

make clean para limpar 
