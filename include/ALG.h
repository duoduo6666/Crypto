#ifndef _ALG_H_
#define _ALG_H_

#define ALGN    256 // ALG number
#define ALGNL   256 // ALG name length

struct node{
  char name[ALGNL];
  int (*fp)(unsigned int argc, char *argv[]);
};

extern struct node alg[ALGN];

#endif