#include "consts256.h"
#include "poly32.h"

/* Simple wrapper to use the 32-bit NTT implementation based on modulus 65537. */

.text
.global cdecl(poly_ntt)
cdecl(poly_ntt):
    /* rdi: result, rsi: input, rdx: ignored (pdata) */
    jmp cdecl(poly32_ntt_avx2)

