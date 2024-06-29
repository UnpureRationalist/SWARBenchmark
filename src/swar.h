#pragma once

#include <cstdint>

long long basicPopcount(const unsigned char *s, long count);

long long bitAndPopcount(const unsigned char *s, long count);

long long gccBuildinPopCount(const unsigned char *s, long count);

// code from Redis: https://github.com/redis/redis/blob/unstable/src/bitops.c
/* Count number of bits set in the binary array pointed by 's' and long
 * 'count' bytes. The implementation of this function is required to
 * work with an input string length up to 512 MB or more
 * (server.proto_max_bulk_len) */
long long redisPopcount(void *s, long count);

// use openmp
long long openmpBasicPopCount(const unsigned char *s, long count);
