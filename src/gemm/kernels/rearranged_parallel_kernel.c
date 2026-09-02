#include "../include/rearranged_parallel_kernel.h"
#include <omp.h>

void gemm_rearranged_parallel(const float *A, const float *B, float *C, int rA, int cA, int cB) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < rA; i++) {
        for (int k = 0; k < cA; k++) {
            float a = A[i * cA + k];
            for (int j = 0; j < cB; j++) {
                C[i * cB + j] += a * B[k * cB + j];
            }
        }
    }
}
