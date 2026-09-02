#ifndef OPENBLAS_PARALLEL_KERNEL_H
#define OPENBLAS_PARALLEL_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif


void saxpy_openblas_parallel(const float *x,
                 float *y,
                 const float a,
                 const int arr_size);

#ifdef __cplusplus
}
#endif

#endif // OPENBLAS_PARALLEL_KERNEL_H