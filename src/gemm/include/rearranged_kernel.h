#ifndef REARRANGED_KERNEL_H
#define REARRANGED_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_rearranged(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // REARRANGED_KERNEL_H
