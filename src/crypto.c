#include <stdio.h>
#include "../include/ERROR.h"
#include "../include/ALG.h"
#include "../include/str.h"

int main(unsigned int argc, char *argv[]){
    if (argc == 1){
        printf(ERROR1);
        return 1;
    }
    if (argc == 2){
        printf(ERROR2);
        return 2;
    }

    unsigned long i=0;
    while (str_cmp(alg[i].name,argv[1]) == 0)
    {
        i++;
        if (i >= ALGN){printf(ERROR3, argv[1]);return 3;}
    }
    alg[i].fp(argc, argv);
    
    return 0;
}
