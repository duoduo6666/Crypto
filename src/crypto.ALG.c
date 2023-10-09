#include "../include/ALG.h"
#include "../include/crypto.CLI.h"

struct node alg[ALGN] = {
  {"SHA-1", &SHA1_CLI},
  {"SHA1", &SHA1_CLI},
  {"SHA-1_Benchmark", &SHA1_Benchmark_CLI},
};