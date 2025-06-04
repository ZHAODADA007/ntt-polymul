#include <immintrin.h>
#include "poly32.h"

/* AVX2 assisted copy then use scalar transforms */

static inline void copy_avx2(poly32 *dst, const poly32 *src) {
    for(int i=0;i<POLY32_N;i+=8) {
        __m256i v = _mm256_loadu_si256((const __m256i*)&src->coeffs[i]);
        _mm256_storeu_si256((__m256i*)&dst->coeffs[i], v);
    }
}

void poly32_ntt_avx2(poly32 *r, const poly32 *a) {
    copy_avx2(r, a);
    poly32_ntt(r, r);
}

void poly32_invntt_avx2(poly32 *r, const poly32 *a) {
    copy_avx2(r, a);
    poly32_invntt(r, r);
}
