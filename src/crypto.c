#include <stdio.h>
#include "../include/SHA-1_x64.h"

#define ERROR1 "请输入算法和消息\n"

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

int main(unsigned int argc, char *argv[]){
    if (argc == 1){
        printf(ERROR1);
        return 1;
    }
    if (argc == 3){
        if (argv[1] == "S"){
            unsigned long len = argv_len(argv[2]);
            unsigned int *hash = SHA1(argv[2],len);
            printf("%x%x%x%x%x\n",hash[0],hash[1],hash[2],hash[3],hash[4]);
        }
    }
    return 0;
}
