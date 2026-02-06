//
// Created by skandan-c-y on 1/8/26.
//

#ifndef LEARNCLEANC_PARALLEL_KERNEL_H
#define LEARNCLEANC_PARALLEL_KERNEL_H

void saxpy_parallel(const float *restrict x,
    float *restrict y,
    float a,
    int arr_size,
    const int num_threads
    );

#endif // LEARNCLEANC_PARALLEL_KERNEL_H
