#ifndef PLAIN_PARALLEL_KERNEL_H
#define PLAIN_PARALLEL_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_plain_parallel(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // PLAIN_PARALLEL_KERNEL_H
