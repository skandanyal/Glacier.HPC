#ifndef OPENBLAS_KERNEL_H
#define OPENBLAS_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void saxpy_openblas(const float *x,
                 float *y,
                 const float a,
                 const int arr_size);

#ifdef __cplusplus
}
#endif

#endif // PLAIN_KERNEL_H





