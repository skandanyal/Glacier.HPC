#ifndef OPENBLAS_KERNEL_H
#define OPENBLAS_KERNEL_H

void saxpy_openblas(const float *x,
                 float *y,
                 const float a,
                 const int arr_size);

#endif // OPENBLAS_KERNEL_H
