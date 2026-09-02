#ifndef STRASSEN_PARALLEL_KERNEL_H
#define STRASSEN_PARALLEL_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_strassen_parallel(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // STRASSEN_PARALLEL_KERNEL_H
