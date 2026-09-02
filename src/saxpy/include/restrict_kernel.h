#ifndef RESTRICT_KERNEL_H
#define RESTRICT_KERNEL_H

#ifdef __cplusplus
#define restrict __restrict
extern "C" {
#endif

void saxpy_restrict(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size);


#ifdef __cplusplus
    }
#endif
#endif //RESTRICT_KERNEL_H