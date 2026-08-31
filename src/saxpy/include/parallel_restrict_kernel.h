#ifndef PARALLEL_RESTRICT_KERNEL_H
#define PARALLEL_RESTRICT_KERNEL_H

void saxpy_parallel_restrict(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size);

#endif // PARALLEL_RESTRICT_KERNEL_H
