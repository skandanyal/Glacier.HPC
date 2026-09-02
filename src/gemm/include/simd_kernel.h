#ifndef SIMD_KERNEL_H
#define SIMD_KERNEL_H

#ifdef __cplusplus
#define restrict __restrict
extern "C" {
#endif

void gemm_simd(const float * restrict A, const float * restrict B, float * restrict C, int rA, int cA, int cB);

#ifdef __cplusplus
}
#endif

#endif // SIMD_KERNEL_H
