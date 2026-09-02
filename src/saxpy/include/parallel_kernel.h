#ifndef PARALLEL_KERNEL_H
#define PARALLEL_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif


void saxpy_parallel(const float * x,
                    float * y,
                    const float a,
                    const int arr_size);

#ifdef __cplusplus
}
#endif

#endif // PARALLEL_KERNEL_H