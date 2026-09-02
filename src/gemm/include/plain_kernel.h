#ifndef PLAIN_KERNEL_H
#define PLAIN_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void gemm_plain(const float *A, const float *B, float *C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // PLAIN_KERNEL_H
