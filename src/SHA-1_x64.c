#include <stdint.h>

uint32_t K[80] = {
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

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
    return (x&y) ^ ((~x)&z);
}
uint32_t Parity(uint32_t x, uint32_t y, uint32_t z){
    return x ^ y ^ z;
}
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
    return (x&y) ^ (x&z) ^ (y&z);
}
uint32_t f(uint8_t t, uint32_t x, uint32_t y, uint32_t z){
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

uint32_t ROTL(uint32_t x, uint8_t n){
    return ((x << n) | (x >> (32 - n)));
}

uint32_t* SHA1_Computation(uint8_t M[64],uint32_t H[5]){
    uint32_t W[80];
    for (uint8_t t = 0; t < 16; t++){
        W[t] = M[t*4]<<24 | M[t*4+1]<<16 | M[t*4+2]<<8 | M[t*4+3];
    }
    for (uint8_t t = 16; t < 80; t++){
        W[t] = ROTL(W[t-3]	^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
    }
    uint32_t a=H[0], b=H[1], c=H[2], d=H[3], e=H[4], T;
    for (uint8_t t = 0; t < 80; t++){
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

uint32_t H[5];

int32_t* SHA1(char message[],uint64_t len){
    H[0] = 0x67452301; H[1] = 0xefcdab89;
    H[2] = 0x98badcfe; H[3] = 0x10325476;
    H[4] = 0xc3d2e1f0;
    uint64_t e = len * 8;
    uint32_t zero = (448-((e+8)%512)) / 8;
    uint64_t M_len = zero+len+9;
    uint8_t M[M_len];
    for (uint64_t i = 0; i < len; i++){
        M[i] = message[i];
    }
    M[len] = 0x80;
    for (uint64_t i = len+1; i < M_len; i++){
        M[i] = 0;
    }
    M[M_len-8]=e>>56; M[M_len-7]=e>>48; M[M_len-6]=e>>40; M[M_len-5]=e>>32;
    M[M_len-4]=e>>24; M[M_len-3]=e>>16; M[M_len-2]=e>>8;  M[M_len-1]=e;
    
    for (uint32_t i = 0; i < M_len; i+=64){
        uint32_t* t = SHA1_Computation(&M[i], H);
        H[0] = t[0]; H[1] = t[1];
        H[2] = t[2]; H[3] = t[3];
        H[4] = t[4];
    }
    return H;
}

char* SHA1_hexstr(char message[], uint64_t len, char hex[16]){
    uint32_t* H = SHA1(message, len);
    static char str[41];

    char i = 0;
    for (char i0 = 0; i0 < 5; i0++){
        for (char i1 = 24; i1 >= 0; i1-=8){
            str[i++] = hex[(uint8_t)(H[i0]>>i1) / 16];
            str[i++] = hex[(uint8_t)(H[i0]>>i1) % 16];
        }
    }
    return str;
}
