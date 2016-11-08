#ifndef USEFUL_H
#define USEFUL_H

#include <string.h>

inline uint32_t rotl1(uint32_t x) {
  return (x << 1) | (x >> 31);
}

__attribute__ ((noinline))
static int * filter(const char *str) {
  int *result = malloc(sizeof(unsigned) * (algo_count + 1));
  unsigned j = 0;
  for (unsigned i=0; i < algo_count; i++) {
    if (!str || strcmp(algo_names[i], str) == 0) {
      result[j++] = i;
    }
  }
  result[j] = -1;
  return result;
}

#endif
