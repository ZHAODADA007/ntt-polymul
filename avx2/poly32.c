#include "poly32.h"

#define ROOT 282u
#define ROOT_INV 64375u
#define INV_N 65281u

static inline uint32_t mod_mul(uint32_t a, uint32_t b) {
    uint64_t t = (uint64_t)a * b;
    uint32_t low = t & 0xFFFF;
    uint32_t high = (t >> 16);
    uint32_t res = low - high;
    if((int32_t)res < 0) res += MOD32;
    if(res >= MOD32) res -= MOD32;
    return res;
}

static uint32_t mod_pow(uint32_t a, uint32_t e) {
    uint64_t r = 1;
    uint64_t b = a;
    while(e) {
        if(e & 1) r = r * b % MOD32;
        b = b * b % MOD32;
        e >>= 1;
    }
    return (uint32_t)r;
}

void poly32_ntt(poly32 *r, const poly32 *a) {
    uint32_t tmp[POLY32_N];
    for(int i=0;i<POLY32_N;i++)
        tmp[i] = a->coeffs[i] % MOD32;

    for(int len=1; len<POLY32_N; len<<=1) {
        uint32_t w_m = mod_pow(ROOT, POLY32_N/(len<<1));
        for(int i=0;i<POLY32_N;i += (len<<1)) {
            uint32_t w = 1;
            for(int j=0;j<len;j++) {
                uint32_t u = tmp[i+j];
                uint32_t v = mod_mul(tmp[i+j+len], w);
                tmp[i+j] = (u + v) % MOD32;
                tmp[i+j+len] = (u + MOD32 - v) % MOD32;
                w = mod_mul(w, w_m);
            }
        }
    }

    for(int i=0;i<POLY32_N;i++)
        r->coeffs[i] = tmp[i];
}

void poly32_invntt(poly32 *r, const poly32 *a) {
    uint32_t tmp[POLY32_N];
    for(int i=0;i<POLY32_N;i++)
        tmp[i] = a->coeffs[i] % MOD32;

    for(int len=POLY32_N/2; len>=1; len>>=1) {
        uint32_t w_m = mod_pow(ROOT_INV, POLY32_N/(len<<1));
        for(int i=0;i<POLY32_N;i += (len<<1)) {
            uint32_t w = 1;
            for(int j=0;j<len;j++) {
                uint32_t u = tmp[i+j];
                uint32_t v = tmp[i+j+len];
                tmp[i+j] = (u + v) % MOD32;
                uint32_t t = (u + MOD32 - v) % MOD32;
                tmp[i+j+len] = mod_mul(t, w);
                w = mod_mul(w, w_m);
            }
        }
    }

    for(int i=0;i<POLY32_N;i++)
        r->coeffs[i] = mod_mul(tmp[i], INV_N);
}
