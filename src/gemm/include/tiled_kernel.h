#ifndef TILED_KERNEL_H
#define TILED_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_tiled(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // TILED_KERNEL_H
