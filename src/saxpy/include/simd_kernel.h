#ifndef SIMD_KERNEL_H
#define SIMD_KERNEL_H


#ifdef __cplusplus
#define restrict __restrict
extern "C" {
#endif

void saxpy_simd(const float * restrict x,
                float * restrict y,
                const float a,
                const int arr_size);


#ifdef __cplusplus
    }
#endif
#endif // SIMD_KERNEL_H
