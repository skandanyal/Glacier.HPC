#ifndef OPENBLAS_KERENL_H
#define OPENBLAS_KERENL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_openblas(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // OPENBLAS_KERENL_H
