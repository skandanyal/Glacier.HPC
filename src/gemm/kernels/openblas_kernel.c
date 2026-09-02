#include "../include/openblas_kerenl.h"
#include <cblas.h>

void gemm_openblas(const float *A, const float *B, float *C, int rA, int cA, int cB) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, rA, cB, cA, 1.0f, A, cA, B, cB, 1.0f, C, cB);
}
