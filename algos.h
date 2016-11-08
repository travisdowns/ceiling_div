#ifndef ALGOS_H
#define ALGOS_H

#include <inttypes.h>
#include <stdbool.h>

#ifndef ALGO_DECL
#define ALGO_DECL static inline
#endif

typedef uint32_t u32;
typedef uint64_t u64;

typedef u32 (*dfun32_t)(u32, u32);
typedef u64 (*dfun64_t)(u64, u64);

inline uint32_t lg32(uint32_t x) {
  return 31U - (uint32_t)__builtin_clz(x);
}

inline uint64_t lg64(uint64_t x) {
  return 63U - (uint64_t)__builtin_clzl(x);
}


ALGO_DECL uint32_t divide_questionc_32(uint32_t p, uint32_t q) {
  uint32_t e = lg32(q);
  return (((int32_t)p - 1) >> e) + 1;
}

ALGO_DECL uint64_t divide_questionc_64(uint64_t p, uint64_t q) {
  uint64_t e = lg64(q);
  return (((int64_t)p - 1) >> e) + 1;
}

ALGO_DECL u32 divide_weather_32(u32 n, u32 d) {
  u32 q1 = n / d;
  if(n) {
    u32 q2 = (n - 1) / d;
    if(q1 == q2) {
      q1++;
    }
  }
  return q1;
}

ALGO_DECL u64 divide_weather_64(u64 n, u64 d) {
  u64 q1 = n / d;
  if(n) {
    u64 q2 = (n - 1) / d;
    if(q1 == q2) {
      q1++;
    }
  }
  return q1;
}

ALGO_DECL u32 divide_chris_32(u32 p, u32 q) {
  int lp=__builtin_ffsl(p);
  int lq=__builtin_ctzl(q);
  return (p>>lq)+(lp<(lq+1)&&lp);

}

ALGO_DECL u64 divide_chris_64(u64 p, u64 q) {
  int lp=__builtin_ffsll(p);
  int lq=__builtin_ctzll(q);
  return (p>>lq)+(lp<(lq+1)&&lp);
}

ALGO_DECL u32 divide_chrisdodd_32(u32 p, u32 q) {
  u32 e = lg32(q);
  /* compute ceil(d/2**e) */
  return p ? ((p-1) >> e) + 1 : 0;
}

ALGO_DECL u64 divide_chrisdodd_64(u64 p, u64 q) {
  u64 e = lg64(q);
  /* compute ceil(d/2**e) */
  return p ? ((p-1) >> e) + 1 : 0;
}

ALGO_DECL uint64_t divide_user23_64(uint64_t p, uint64_t q) {
  uint64_t exponent = lg64(q);
  uint64_t mask = q - 1;
  //     v divide
  return (p >> exponent) + (((p & mask) + mask) >> exponent);
  //                       ^ round up
}

ALGO_DECL uint64_t divide_user23_variant_64(uint64_t p, uint64_t q) {
  uint64_t exponent = lg32(q);
  uint64_t mask = q - 1;
  //     v divide
  return (p >> exponent) + ((p & mask) != 0);
  //                       ^ round up
}

ALGO_DECL uint32_t divide_chux_32(uint32_t p, uint32_t q) {
  bool round_up = p & (q-1);
  return (p >> lg32(q)) + round_up;
}

ALGO_DECL uint64_t divide_chux_64(uint64_t p, uint64_t q) {
  bool round_up = p & (q-1);
  return (p >> lg64(q)) + round_up;
} 

ALGO_DECL uint32_t divide_user23_32(uint32_t p, uint32_t q) {
  uint32_t exponent = lg32(q);
  uint32_t mask = q - 1;
  //     v divide
  return (p >> exponent) + (((p & mask) + mask) >> exponent);
  //                       ^ round up
}

ALGO_DECL uint32_t divide_user23_variant_32(uint32_t p, uint32_t q) {
  uint32_t exponent = lg32(q);
  uint32_t mask = q - 1;
  //     v divide
  return (p >> exponent) + ((p & mask) != 0);
  //                       ^ round up
}

ALGO_DECL uint32_t ref_32(uint32_t p, uint32_t q) {
  uint32_t exponent = lg32(q);
  uint32_t mask = q - 1;
  //     v divide
  return (p >> exponent) + ((p & mask) != 0);
  //                       ^ round up
}

ALGO_DECL uint32_t divide32_ref(uint32_t p, uint32_t q) {
  uint32_t res = p / q;
  return res * q != p ? res + 1 : res;
}

ALGO_DECL uint32_t divide_plusq_32(uint32_t p, uint32_t q) {
  uint32_t e = lg32(q);
  return (p + q - 1) >> e;
}

ALGO_DECL uint64_t divide_plusq_64(uint64_t p, uint64_t q) {
  uint64_t e = lg64(q);
  return (p + q - 1) >> e;
}

/* just returns 0, uses to test call/ret and benchmark overhead */
ALGO_DECL uint32_t divide_dummy_32(uint32_t p, uint32_t q) {
  return p + q;
}

ALGO_DECL uint64_t divide_dummy_64(uint64_t p, uint64_t q) {
  return p + q;
}

ALGO_DECL void dummy_noarg() {
}

#endif
