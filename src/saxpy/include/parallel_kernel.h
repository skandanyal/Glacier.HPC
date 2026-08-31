#ifndef PARALLEL_KERNEL_H
#define PARALLEL_KERNEL_H

void saxpy_parallel(const float * x,
                    float * y,
                    const float a,
                    const int arr_size);

#endif // PARALLEL_KERNEL_H
