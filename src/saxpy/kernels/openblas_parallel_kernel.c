#include "../include/openblas_parallel_kernel.h"

#include <cblas.h>

void saxpy_openblas_parallel(const float *x, float *y, const float a, const int arr_size) {
    cblas_saxpy(arr_size, a, x, 1, y, 1);
}
