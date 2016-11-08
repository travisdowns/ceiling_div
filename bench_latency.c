#include <time.h>
#include <stdio.h>

#include "algos.h"
#include "allx.h"
#include "useful.h"

const unsigned ITERS = 1000000000;
const unsigned UNROLL = 1;
const double   GHZ = 2.59;

volatile int blackhole = 0;

#define BFUNC_C(fname) uint32_t bench_c_ ## fname(uint32_t p, uint32_t q) { \
    (void)q;								\
    uint32_t total = p;							\
    for (unsigned i=0; i < ITERS; i++) {				\
      total += fname(total, 8);						\
    }									\
    return total;							\
  }

#define BFUNC_I(fname) uint32_t bench_i_ ## fname(uint32_t p, uint32_t q) { \
    uint32_t total = p;							\
    for (unsigned i=0; i < ITERS; i++) {				\
      total += fname(total, q);						\
    }									\
    return total;							\
  }

#define BFUNC_V(fname) uint32_t bench_v_ ## fname(uint32_t p, uint32_t q) { \
    uint32_t total = p;							\
    for (unsigned i=0; i < ITERS; i++) {				\
      total += fname(total, q);						\
      q = rotl1(q);							\
    }									\
    return total;							\
  }

#define BFUNCS_C(fname) BFUNC_C(fname##_32) BFUNC_C(fname##_64)
#define BFUNCS_I(fname) BFUNC_I(fname##_32) BFUNC_I(fname##_64)
#define BFUNCS_V(fname) BFUNC_V(fname##_32) BFUNC_V(fname##_64)


X_MACRO(BFUNCS_C)
X_MACRO(BFUNCS_I)
X_MACRO(BFUNCS_V)


#define BFUNC_C32(a) &bench_c_##a##_32,
#define BFUNC_C64(a) &bench_c_##a##_64,
#define BFUNC_I32(a) &bench_i_##a##_32,
#define BFUNC_I64(a) &bench_i_##a##_64,
#define BFUNC_V32(a) &bench_v_##a##_32,
#define BFUNC_V64(a) &bench_v_##a##_64,


typedef uint32_t (*bfunc_t)(uint32_t p, uint32_t q); 

#define BPTRS(letter)					  \
  bfunc_t bfuncs_ ## letter ## 32[] = { X_MACRO(BFUNC_ ## letter ## 32) }; \
  bfunc_t bfuncs_ ## letter ## 64[] = { X_MACRO(BFUNC_ ## letter ## 64) }; 

BPTRS(C)
BPTRS(I)
BPTRS(V)

const bfunc_t func = 0;

volatile uint32_t x = 123456, y = 256, sink;

void bench_one(bfunc_t f, const char *fname, const char *suffix) {
  printf("%23s%s", fname, suffix);
  //sink = (*f)(x, y); /* warm cache */
  clock_t start = clock();	       
  sink = (*f)(x, y);
  clock_t end = clock(), elapsed = end - start;
  double ns = (double)elapsed*1000000000/CLOCKS_PER_SEC/ITERS/UNROLL;
  printf("%16.2f %10.2f\n", ns, ns * GHZ);
}

void bench_index(int indexes[], bfunc_t f32[], bfunc_t f64[], const char *name) {
  printf("\n\n==============================\nBench: %s\n==============================\n", name);
  printf("%26s%16s%10s\n", "Function", "ns/call", "cycles");
  for (int i=0; indexes[i] != -1; i++) {
    unsigned idx = indexes[i];
    const char *fname = algo_names[idx];
    bench_one(f32[idx], fname, "_32");
    bench_one(f64[idx], fname, "_64");
  }
}

int main(int argc, char** argv) {
  int *indexes = filter(argc == 1 ? NULL : argv[1]);
  bench_index(indexes, bfuncs_C32, bfuncs_C64, "Compile-time constant Q");
  bench_index(indexes, bfuncs_I32, bfuncs_I64, "Invariant Q");
  bench_index(indexes, bfuncs_V32, bfuncs_V64, "Variable Q");
}



