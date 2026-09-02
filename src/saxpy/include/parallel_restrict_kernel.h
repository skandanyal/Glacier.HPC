#ifndef PARALLEL_RESTRICT_KERNEL_H
#define PARALLEL_RESTRICT_KERNEL_H

#ifdef __cplusplus
#define restrict __restrict
extern "C" {
#endif


void saxpy_parallel_restrict(const float * restrict x,
                    float * restrict y,
                    const float a,
                    const int arr_size);


#ifdef __cplusplus
}
#endif


#endif // PARALLEL_RESTRICT_KERNEL_H




