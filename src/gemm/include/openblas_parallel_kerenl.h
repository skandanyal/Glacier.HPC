#ifndef OPENBLAS_PARALLEL_KERENL_H
#define OPENBLAS_PARALLEL_KERENL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_openblas_parallel(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // OPENBLAS_PARALLEL_KERENL_H
