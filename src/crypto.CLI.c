#include <stdio.h>
#include "../include/str.h"

#include "../include/SHA-1_x64.h"
int SHA1_CLI(unsigned int argc, char *argv[]){
    printf("%s\n",SHA1_hexstr(argv[2],str_len(argv[2]),"0123456789abcdef"));
    return 0;
}
