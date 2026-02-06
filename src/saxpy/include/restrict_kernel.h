//
// Created by skandan-c-y on 1/8/26.
//

#ifndef LEARNCLEANC_RESTRICT_KERNEL_H
#define LEARNCLEANC_RESTRICT_KERNEL_H

void saxpy_restrict(const float * restrict x, float * restrict y, float a, int arr_size);

#endif //LEARNCLEANC_RESTRICT_KERNEL_H