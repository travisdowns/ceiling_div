#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "algos.h"
#include "allx.h"
#include "useful.h"


typedef int (*vfunc_t)();

#define VFUNC(fname) \
int validate_ ## fname () { \
  u32 p = 0, q = 1;   \
  do { \
    do { \
      u32 res_ref  = ref_32(p, q); \
      u32 res_test = fname(p, q); \
      if (res_ref != res_test) { \
	printf("**** Test failed for p=%u, q=%u, expected=%u, actual=%u\n", p, q, res_ref, res_test); \
	return 0;							\
      } \
    } while (++p != 0); \
    printf("\r%2d%% complete...", lg32(q << 1)*100/32);	\
    fflush(stdout); \
  } while ((q <<= 1) != 0); \
  return 1; \
};

#define VFUNC32(fname) VFUNC(fname##_32)
#define VFUNC64(fname) VFUNC(fname##_64)

X_MACRO(VFUNC32)
X_MACRO(VFUNC64)

#define VFUNC_PTR32(a) &validate_##a##_32,
#define VFUNC_PTR64(a) &validate_##a##_32,

vfunc_t vfuncs32[] = { X_MACRO(VFUNC_PTR32) };
vfunc_t vfuncs64[] = { X_MACRO(VFUNC_PTR64) };

void validate_one(vfunc_t f, const char *fname, const char *suffix) {
  printf("Validating function: %16s%s...\n", fname, suffix);
  clock_t begin = clock();
  if ((*f)()) {
    printf("\rValidated OK in %4d secs\n", (int)((clock() - begin) / CLOCKS_PER_SEC));
  }
}

void validate_index(int indexes[]) {
  for (int i=0; indexes[i] != -1; i++) {
    unsigned idx = indexes[i];
    const char *fname = algo_names[idx];
    validate_one(vfuncs32[idx], fname, "_32");
    validate_one(vfuncs64[idx], fname, "_64");
  }
}

int main(int argc, const char** argv) {
  validate_index(filter(argc, argv));
}
