#ifndef DECLS_H
#define DECLS_H
#include <inttypes.h>
#include "allx.h"

/* all the declaration of the algorithms, without the body */

#define ALGO_DECL32(fname) uint32_t fname##_32 (uint32_t p, uint32_t q);
#define ALGO_DECL64(fname) uint64_t fname##_64 (uint64_t p, uint64_t q);

X_MACRO(ALGO_DECL32)
X_MACRO(ALGO_DECL64)

void dummy_noarg();

#endif
