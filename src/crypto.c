#include <stdio.h>
#include "SHA-1_x64.h"

long argv_len(char const str[]){
    unsigned long i = 0;
    char ASCII = 0xFF;
    while (ASCII != 0)
    {
        i++;
        ASCII = str[i];
    }
    return i;
}

int main(int argc, char const *argv[]){
    unsigned long len = argv_len(argv[1]);
    unsigned int *hash = SHA1(argv[1],len);
    printf("%x%x%x%x%x\n",hash[0],hash[1],hash[2],hash[3],hash[4]);
    return 0;
}
