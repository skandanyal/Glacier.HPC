#ifndef TILED_PARALLEL_KERNEL_H
#define TILED_PARALLEL_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_tiled_parallel(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // TILED_PARALLEL_KERNEL_H
