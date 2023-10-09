#include <stdio.h>
#include <time.h>
#include "../include/str.h"

#include "../include/SHA-1_x64.h"
int SHA1_CLI(unsigned int argc, char *argv[]){
    printf("%s\n",SHA1_hexstr(argv[2],str_len(argv[2]),"0123456789abcdef"));
    return 0;
}
int SHA1_Benchmark_CLI(unsigned int argc, char *argv[]){
    clock_t start_t, end_t;
    double total_t;
    uint32_t M[64] = {0};
    uint32_t H[5] = {0};

    start_t = clock();
    for (size_t i = 0; i < 1000000; i++){
        // SHA1("", 0);
        SHA1_Computation(M, H);
    }
    end_t = clock();

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%fMH/s\n", (1000000/total_t)/1000000);

    return 0;
}