#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

unsigned int const K[80] = {
    0x5a827999,0x5a827999,0x5a827999,0x5a827999,
    0x5a827999,0x5a827999,0x5a827999,0x5a827999,
    0x5a827999,0x5a827999,0x5a827999,0x5a827999,
    0x5a827999,0x5a827999,0x5a827999,0x5a827999,
    0x5a827999,0x5a827999,0x5a827999,0x5a827999,

    0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,
    0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,
    0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,
    0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,
    0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,0x6ed9eba1,

    0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,
    0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,
    0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,
    0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,
    0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,0x8f1bbcdc,

    0xca62c1d6,0xca62c1d6,0xca62c1d6,0xca62c1d6,
    0xca62c1d6,0xca62c1d6,0xca62c1d6,0xca62c1d6,
    0xca62c1d6,0xca62c1d6,0xca62c1d6,0xca62c1d6,
    0xca62c1d6,0xca62c1d6,0xca62c1d6,0xca62c1d6,
    0xca62c1d6,0xca62c1d6,0xca62c1d6,0xca62c1d6,
};

unsigned int Ch(unsigned int x, unsigned int y, unsigned int z){
    return (x&y) ^ ((~x)&z);
}
unsigned int Parity(unsigned int x, unsigned int y, unsigned int z){
    return x ^ y ^ z;
}
unsigned int Maj(unsigned int x, unsigned int y, unsigned int z){
    return (x&y) ^ (x&z) ^ (y&z);
}
unsigned int f(unsigned char t, unsigned int x, unsigned int y, unsigned int z){
    if (t <= 19){
        return Ch(x,y,z);
    }
    if (t <= 39){
        return Parity(x,y,z);
    }
    if (t <= 59){
        return Maj(x,y,z);
    }
    if (t <= 79){
        return Parity(x,y,z);
    }
}

unsigned int ROTL(unsigned int x, unsigned char n){
    return ((x << n) | (x >> (32 - n)));
}

unsigned int* SHA1_Computation(unsigned char M[64],unsigned int H[5]){
    unsigned int W[80];
    for (unsigned char t = 0; t < 16; t++){
        W[t] = M[t*4]<<24 | M[t*4+1]<<16 | M[t*4+2]<<8 | M[t*4+3];
    }
    for (unsigned char t = 16; t < 80; t++){
        W[t] = ROTL(W[t-3]	^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
    }
    unsigned int a=H[0], b=H[1], c=H[2], d=H[3], e=H[4], T;
    for (unsigned char t = 0; t < 80; t++){
        T = ROTL(a,5) + f(t,b,c,d) + e + K[t] + W[t];
        e = d;
        d = c;
        c = ROTL(b,30);
        b = a;
        a = T;
    }
    H[0] = (a+H[0]);
    H[1] = (b+H[1]);
    H[2] = (c+H[2]);
    H[3] = (d+H[3]);
    H[4] = (e+H[4]);
    
    return H;
}

int* SHA1(char const message[],unsigned long const len){
    static unsigned int H[5] = {0x67452301,0xefcdab89,0x98badcfe,0x10325476,0xc3d2e1f0};
    unsigned long e = len * 8;
    unsigned int zero = (448-((e+8)%512)) / 8;
    unsigned long M_len = zero+len+9;
    unsigned char M[M_len];
    for (unsigned long i = 0; i < len; i++){
        M[i] = message[i];
    }
    M[len] = 0x80;
    for (unsigned long i = len+1; i < M_len; i++){
        M[i] = 0;
    }
    M[M_len-8]=e>>56;M[M_len-7]=e>>48;M[M_len-6]=e>>40;M[M_len-5]=e>>32;
    M[M_len-4]=e>>24;M[M_len-3]=e>>16;M[M_len-2]=e>>8;M[M_len-1]=e;
    
    for (unsigned int i = 0; i < M_len; i+=64){
        unsigned int* t = SHA1_Computation(&M[i], H);
        H[0] = t[0]; H[1] = t[1];
        H[2] = t[2]; H[3] = t[3];
        H[4] = t[4];
    }
    return H;
}

void ctrl_exit(int signum)
{
    printf("\n");
    exit(0);
}

void SHA1_benchmark(){
    char data[] = "abc";
    unsigned int len = 3;
    clock_t clock_sec= CLOCKS_PER_SEC, start, end;
    signal(SIGINT, ctrl_exit);
    while (1){
        start = clock();
        for(unsigned int i = 0; i < 1024; i++){
            SHA1(data,len);
        }
        end = clock();
        printf("\r%lu/s",clock_sec/(end-start)*1024);
    }
}
