#ifndef ALGOS_H
#define ALGOS_H

#include <inttypes.h>
#include <stdbool.h>
#include <immintrin.h>

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

/* 
imull $0xff, %esi, %ebx         
decl %edi                       
pextl %ebx, %edi, %eax          
incl %eax                       
retq   
*/

ALGO_DECL unsigned divide_peter_32(unsigned p, unsigned q) {
    unsigned mask = -(unsigned)(p!=0);  // TEST+SETCC+NEG
    unsigned e = lg32(q);
    unsigned nonzero_result = ((p-1) >> e) + 1;
    return nonzero_result & mask;
}

ALGO_DECL unsigned long divide_peter_64(unsigned long p, unsigned long q) {
    unsigned long mask = -(unsigned long)(p!=0);  // TEST+SETCC+NEG
    unsigned long e = lg64(q);
    unsigned long nonzero_result = ((p-1) >> e) + 1;
    return nonzero_result & mask;
}

ALGO_DECL unsigned stoke32_32(unsigned p, unsigned q) {
  return (((unsigned long)p - 1) >> lg32(q)) + 1;
}

ALGO_DECL unsigned stoke32_64(unsigned long p, unsigned long q) {
    unsigned exponent = __builtin_ctz(q);
  //     v divide
  unsigned ret = (p >> exponent);

  return (ret << exponent) == p ? ret : ret + 1;
}
  

ALGO_DECL unsigned stoke_mul_32(unsigned p, unsigned q) {
  unsigned e = q * 0xffffffff;
  return p == 0 ? p : _pext_u32(p - 1, e) + 1;
}

ALGO_DECL uint64_t stoke_mul_64(uint64_t p, uint64_t q) {
  uint64_t e = q * 0xff;
  return p == 0 ? 0 : _pext_u64(p, e) + 1;
}

ALGO_DECL unsigned div_stoke_32(unsigned p, unsigned q) {
  unsigned exponent = __builtin_ctz(q);
  //     v divide
  unsigned ret = (p >> exponent);

  return (ret << exponent) == p ? ret : ret + 1;
}

ALGO_DECL unsigned div_stoke_64(unsigned p, unsigned q) {
  unsigned exponent = __builtin_ctz(q);
  //     v divide
  unsigned ret = (p >> exponent);

  return (ret << exponent) == p ? ret : ret + 1;
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
  int lp=__builtin_ffs(p);
  int lq=__builtin_ctz(q);
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
  uint64_t exponent = lg64(q);
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
