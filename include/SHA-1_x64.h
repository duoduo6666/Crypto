#ifndef _SHA1_x64_H_
#define _SHA1_x64_H_

unsigned int* SHA1_Computation(unsigned char M[64],unsigned int H[5]);

int* SHA1(char message[],unsigned long len);
char* SHA1_hexstr(char message[],unsigned long len, char hex[16]);

void SHA1_benchmark();

#endif