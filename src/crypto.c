#include <stdio.h>
#include "../include/SHA-1_x64.h"

#define ALGN 256

#define ERROR1 "请输入算法和参数\n"
#define ERROR2 "请输入参数\n"
#define ERROR3 "不支持 %s 算法\n"

unsigned long str_len(char str[]){
    unsigned long i = 0;
    char ASCII = 0xFF;
    while (ASCII != 0)
    {
        i++;
        ASCII = str[i];
    }
    return i;
}

char str_cmp(char str0[],char str1[]){
    unsigned long i = 0;
    while (str0[i] == str1[i]){   
        if ((str0[i] | str1[i]) == 0){return 1;}
        i++;
    }
    return 0;
}

int SHA1_CLI(unsigned int argc, char *argv[]){
    printf("%s\n",SHA1_hexstr(argv[2],str_len(argv[2]),"0123456789abcdef"));
    return 0;
}

struct node{
  char name[256];
  int (*fp)(unsigned int argc, char *argv[]);
};

struct node alg[ALGN] = {
    {"SHA-1", &SHA1_CLI},
    {"SHA1", &SHA1_CLI},
};

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
