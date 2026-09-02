#include "../include/plain_kernel.h"

void gemm_plain(const float *A, const float *B, float *C, int rA, int cA, int cB) {
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cB; j++) {
            float sum = 0.0f;
            for (int k = 0; k < cA; k++) {
                sum += A[i * cA + k] * B[k * cB + j];
            }
            C[i * cB + j] += sum;
        }
    }
}
