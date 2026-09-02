#include "../include/simd_kernel.h"
#include <immintrin.h>

void gemm_simd(const float * restrict A, const float * restrict B, float * restrict C, int rA, int cA, int cB) {
    for (int i = 0; i < rA; i++) {
        for (int k = 0; k < cA; k++) {
            __m256 a_vec = _mm256_set1_ps(A[i * cA + k]);
            int j = 0;
            for (; j <= cB - 8; j += 8) {
                __m256 c_vec = _mm256_loadu_ps(&C[i * cB + j]);
                __m256 b_vec = _mm256_loadu_ps(&B[k * cB + j]);
                c_vec = _mm256_fmadd_ps(a_vec, b_vec, c_vec);
                _mm256_storeu_ps(&C[i * cB + j], c_vec);
            }
            for (; j < cB; j++) {
                C[i * cB + j] += A[i * cA + k] * B[k * cB + j];
            }
        }
    }
}
