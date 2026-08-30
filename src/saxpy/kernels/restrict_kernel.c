#include "../include/restrict_kernel.h"

void saxpy_restrict(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size) {
    for (long i=0; i<arr_size; i++) {
        y[i] = a * x[i] + y[i];
    }

    // float sink = y[arr_size] + 1;
}