#include <stdio.h>
#include <stdlib.h>
#include "poly32.h"

int main() {
    poly32 a, b, c;
    for(int i=0;i<POLY32_N;i++)
        a.coeffs[i] = rand() % MOD32;

    poly32_ntt(&b, &a);
    poly32_invntt(&c, &b);

    for(int i=0;i<POLY32_N;i++) {
        if(a.coeffs[i] % MOD32 != c.coeffs[i]) {
            printf("Mismatch at %d\n", i);
            return 1;
        }
    }

    printf("NTT32 test passed\n");
    return 0;
}
