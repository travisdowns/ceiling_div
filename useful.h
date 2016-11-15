#ifndef USEFUL_H
#define USEFUL_H

#include <string.h>

inline uint32_t rotl1(uint32_t x) {
  return (x << 1) | (x >> 31);
}

__attribute__ ((noinline))
static int * filter(const char argc, const char **argv) {
  int *result = malloc(sizeof(unsigned) * (algo_count + 1));
  unsigned j = 0;
  for (unsigned i=0; i < algo_count; i++) {
    if (argc == 1) {
      result[j++] = i;
    } else {
      for (int k = 1; k < argc; k++) {
	if (strcmp(algo_names[i], argv[k]) == 0) {
	  result[j++] = i;
	  break;
	}
      }
    }
  }
  result[j] = -1;
  return result;
}

#endif
