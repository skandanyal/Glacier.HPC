#include "../include/parallel_kernel.h"
#include <omp.h>

void saxpy_parallel_restrict(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size) {
    #pragma omp parallel for schedule(static)
    for (long i = 0; i < arr_size; i++) {
        y[i] = a * x[i] + y[i];
    }
}