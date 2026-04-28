#include <stdio.h>
#include <stdlib.h>

void bits(char *op1, char *opBin, char *op2) {
    int val1 = atoi(op1);
    int val2 = atoi(op2);
    int result = 0;
    
    switch (*opBin) {
        case '&':
            result = val1 & val2;
            break;
        case '|':
            result = val1 | val2;
            break;
        case '^':
            result = val1 ^ val2;
            break;
        default:
            printf("Operador inválido.\n");
            return;
    }
    
    printf("Resultado bits: %d\n", result);
}