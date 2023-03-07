#include <stdint.h>

#ifndef _SHA1_x64_H_
#define _SHA1_x64_H_

uint32_t* SHA1_Computation(uint32_t M[64],uint32_t H[5]);

int32_t* SHA1(char message[],uint64_t len);
char* SHA1_hexstr(char message[],uint64_t len, char hex[16]);

#endif