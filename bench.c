#include <time.h>
#include <stdio.h>

#include "decls.h"
#include "useful.h"

const unsigned ITERS = 1000000000;
const unsigned UNROLL = 1;

volatile int blackhole = 0;

#define BFUNC(fname) void bench_ ## fname(uint32_t p, uint32_t q) {	\
  for (unsigned i=0; i < ITERS; i++) { \
    fname(p, q);		       \
  } \
}

#define BFUNC32(fname) BFUNC(fname##_32)
#define BFUNC64(fname) BFUNC(fname##_64)
#define BFUNCS(fname) BFUNC32(fname) BFUNC64(fname)

X_MACRO(BFUNCS)
//BFUNC(dummy_noarg)

#define BFUNC_PTR32(a) &bench_##a##_32,
#define BFUNC_PTR64(a) &bench_##a##_64,

typedef void (*bfunc_t)(); 

bfunc_t bfuncs32[] = { X_MACRO(BFUNC_PTR32) };
bfunc_t bfuncs64[] = { X_MACRO(BFUNC_PTR64) };

const bfunc_t func = 0;

volatile uint32_t x = 123456, y = 256;

void bench_one(bfunc_t f, const char *fname, const char *suffix) {
  printf("%23s%s", fname, suffix);
  (*f)(x, y); /* warm cache */
  clock_t start = clock();	       
  (*f)(x, y);
  clock_t end = clock(), elapsed = end - start;
  printf("%16.2f\n", (double)elapsed*1000000000/CLOCKS_PER_SEC/ITERS/UNROLL);
}

void bench_index(int indexes[]) {
  printf("%26s%16s\n", "Function", "ns/call");
  for (int i=0; indexes[i] != -1; i++) {
    unsigned idx = indexes[i];
    const char *fname = algo_names[idx];
    bench_one(bfuncs32[idx], fname, "_32");
    bench_one(bfuncs64[idx], fname, "_64");
  }
}

int main(int argc,const char** argv) {
  bench_index(filter(argc, argv));
}



