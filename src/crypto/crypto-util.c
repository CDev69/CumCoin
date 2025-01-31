
#include <memory.h>
#include <stdio.h>

#include "crypto-util.h"

#ifdef _WIN32
	#include <windows.h>
#endif

void sodium_memzero(void* pnt, size_t len){
#ifdef _WIN32
    SecureZeroMemory(pnt, len);
#else
    volatile unsigned char *volatile pnt_ = (volatile unsigned char *volatile) pnt;
    size_t i = (size_t) 0U;

    while (i < len) {
        pnt_[i++] = 0U;
    }
#endif
}

int sodium_compare(const void* a1, const void* a2, size_t len){
  const volatile unsigned char *volatile b1 = (const volatile unsigned char *) a1;
  const volatile unsigned char *volatile b2 = (const volatile unsigned char *) a2;
  size_t                 i;
  volatile unsigned char gt = 0U;
  volatile unsigned char eq = 1U;
  uint16_t               x1, x2;

  i = len;
  while (i != 0U) {
    i--;
    x1 = b1[i];
    x2 = b2[i];
    gt |= ((x2 - x1) >> 8) & eq;
    eq &= ((x2 ^ x1) - 1) >> 8;
  }
  return (int) (gt + gt + eq) - 1;
}

int sodium_is_zero(const void * data, const size_t nlen)
{
  const unsigned char *n = data;
  size_t                 i;
  volatile unsigned char d = 0U;

  for (i = 0U; i < nlen; i++) {
    d |= n[i];
  }
  return 1 & ((d - 1) >> 8);
}
