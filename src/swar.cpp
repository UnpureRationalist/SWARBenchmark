#include "swar.h"

#include <omp.h>

long long basicPopcount(const unsigned char *s, long count) {
  long long bits = 0;
  for (long i = 0; i < count; ++i) {
    for (int j = 0; j < 8; ++j) {
      bits += s[i] & (1 << j);
    }
  }
  return bits;
}

long long bitAndPopcount(const unsigned char *s, long count) {
  long long bits = 0;
  for (long i = 0; i < count; ++i) {
    unsigned char c = s[i];
    while (c) {
      bits++;
      c &= c - 1;
    }
  }
  return bits;
}

long long gccBuildinPopCount(const unsigned char *s, long count) {
  long long bits = 0;
  for (long i = 0; i < count; ++i) {
    bits += __builtin_popcount(s[i]);
  }
  return bits;
}

long long openmpBasicPopCount(const unsigned char *s, long count) {
  long long bits = 0;
#pragma omp parallel for reduction(+ : bits) num_threads(2)
  for (long i = 0; i < count; ++i) {
    for (int j = 0; j < 8; ++j) {
      bits += s[i] & (1 << j);
    }
  }
  return bits;
}

// code from Redis: https://github.com/redis/redis/blob/unstable/src/bitops.c
long long redisPopcount(void *s, long count) {
  long long bits = 0;
  unsigned char *p = reinterpret_cast<unsigned char *>(s);
  uint32_t *p4;
  static const unsigned char bitsinbyte[256] = {
      0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2,
      3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
      3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
      6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
      3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4,
      5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
      6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

  /* Count initial bytes not aligned to 32 bit. */
  while ((unsigned long)p & 3 && count) {
    bits += bitsinbyte[*p++];
    count--;
  }

  /* Count bits 28 bytes at a time */
  p4 = (uint32_t *)p;
  while (count >= 28) {
    uint32_t aux1, aux2, aux3, aux4, aux5, aux6, aux7;

    aux1 = *p4++;
    aux2 = *p4++;
    aux3 = *p4++;
    aux4 = *p4++;
    aux5 = *p4++;
    aux6 = *p4++;
    aux7 = *p4++;
    count -= 28;

    aux1 = aux1 - ((aux1 >> 1) & 0x55555555);
    aux1 = (aux1 & 0x33333333) + ((aux1 >> 2) & 0x33333333);
    aux2 = aux2 - ((aux2 >> 1) & 0x55555555);
    aux2 = (aux2 & 0x33333333) + ((aux2 >> 2) & 0x33333333);
    aux3 = aux3 - ((aux3 >> 1) & 0x55555555);
    aux3 = (aux3 & 0x33333333) + ((aux3 >> 2) & 0x33333333);
    aux4 = aux4 - ((aux4 >> 1) & 0x55555555);
    aux4 = (aux4 & 0x33333333) + ((aux4 >> 2) & 0x33333333);
    aux5 = aux5 - ((aux5 >> 1) & 0x55555555);
    aux5 = (aux5 & 0x33333333) + ((aux5 >> 2) & 0x33333333);
    aux6 = aux6 - ((aux6 >> 1) & 0x55555555);
    aux6 = (aux6 & 0x33333333) + ((aux6 >> 2) & 0x33333333);
    aux7 = aux7 - ((aux7 >> 1) & 0x55555555);
    aux7 = (aux7 & 0x33333333) + ((aux7 >> 2) & 0x33333333);
    bits += ((((aux1 + (aux1 >> 4)) & 0x0F0F0F0F) + ((aux2 + (aux2 >> 4)) & 0x0F0F0F0F) +
              ((aux3 + (aux3 >> 4)) & 0x0F0F0F0F) + ((aux4 + (aux4 >> 4)) & 0x0F0F0F0F) +
              ((aux5 + (aux5 >> 4)) & 0x0F0F0F0F) + ((aux6 + (aux6 >> 4)) & 0x0F0F0F0F) +
              ((aux7 + (aux7 >> 4)) & 0x0F0F0F0F)) *
             0x01010101) >>
            24;
  }
  /* Count the remaining bytes. */
  p = (unsigned char *)p4;
  while (count--) bits += bitsinbyte[*p++];
  return bits;
}
