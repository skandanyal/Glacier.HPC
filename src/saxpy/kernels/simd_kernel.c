#include "../include/simd_kernel.h"
#include <immintrin.h>

void saxpy_simd(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size) {
    __m256 vec_a = _mm256_set1_ps(a);

    int i = 0;

    for (; i <= arr_size - 8; i += 8) {
        __m256 vec_x = _mm256_loadu_ps(&x[i]);
        __m256 vec_y = _mm256_loadu_ps(&y[i]);
        __m256 vec_res = _mm256_fmadd_ps(vec_x, vec_a, vec_y);
        _mm256_storeu_ps(&y[i], vec_res);
    }

    for (; i < arr_size; ++i) {
        y[i] = a * x[i] + y[i];
    }
}
