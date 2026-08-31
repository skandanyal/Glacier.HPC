#ifndef RESTRICT_KERNEL_H
#define RESTRICT_KERNEL_H

void saxpy_restrict(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size);

#endif //RESTRICT_KERNEL_H