#ifndef SIMD_KERNEL_H
#define SIMD_KERNEL_H

void saxpy_simd(const float * restrict x,
                float * restrict y,
                const float a,
                const int arr_size);

#endif // SIMD_KERNEL_H
