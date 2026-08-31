#include "../include/openblas_kernel.h"

#include <cblas.h>

void saxpy_openblas(const float *x, float *y, const float a, const int arr_size) {
    cblas_saxpy(arr_size, a, x, 1, y, 1);
}
