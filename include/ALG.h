#include "../include/CLI.h"

#define ALGN    256 // ALG number
#define ALGNL   256 // ALG name length

struct node{
  char name[ALGNL];
  int (*fp)(unsigned int argc, char *argv[]);
};
struct node alg[ALGN] = {
    {"SHA-1", &SHA1_CLI},
    {"SHA1", &SHA1_CLI},
};