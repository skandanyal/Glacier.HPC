#include "../include/tiled_kernel.h"

#define BLOCK_SIZE 32

void gemm_tiled(const float *A, const float *B, float *C, int rA, int cA, int cB) {
    for (int ii = 0; ii < rA; ii += BLOCK_SIZE) {
        for (int kk = 0; kk < cA; kk += BLOCK_SIZE) {
            for (int jj = 0; jj < cB; jj += BLOCK_SIZE) {
                int i_max = (ii + BLOCK_SIZE < rA) ? ii + BLOCK_SIZE : rA;
                int k_max = (kk + BLOCK_SIZE < cA) ? kk + BLOCK_SIZE : cA;
                int j_max = (jj + BLOCK_SIZE < cB) ? jj + BLOCK_SIZE : cB;
                for (int i = ii; i < i_max; i++) {
                    for (int k = kk; k < k_max; k++) {
                        float a = A[i * cA + k];
                        for (int j = jj; j < j_max; j++) {
                            C[i * cB + j] += a * B[k * cB + j];
                        }
                    }
                }
            }
        }
    }
}
