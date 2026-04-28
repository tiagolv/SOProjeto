#include"shell.h"
#include<math.h>

void calc(char *value1, char *op, char *value2){
    float val1 = atof(value1);
    float val2 = atof(value2);

    switch (*op)
    {
    case '+':
        printf("%f + %f = %f\n", val1, val2, val1 + val2);
        break;
    case '-':
        printf("%f - %f = %f\n", val1, val2, val1 - val2);
        break;
    case '*':
        printf("%f x %f = %f\n", val1, val2, val1 * val2);
        break;
    case ('/'):
        if(val2 == 0){ printf("Impossível dividir por 0\n");}else
        {printf("%f / %f = %f\n", val1, val2, val1 / val2);}
        break;
    case '^':
        printf("%f^%f = %f\n", val1, val2, powf(val1, val2));
        break;
    default:
        printf("Unkown character\n");
        break;
    }
}