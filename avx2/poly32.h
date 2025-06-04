#ifndef POLY32_H
#define POLY32_H

#include <stdint.h>

#define POLY32_N 256
#define MOD32 998244353u

typedef struct {
    uint32_t coeffs[POLY32_N];
} poly32;

void poly32_ntt(poly32 *r, const poly32 *a);
void poly32_invntt(poly32 *r, const poly32 *a);

#endif
