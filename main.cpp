#include <iostream>
#include <vector>
#include "omp.h"

int main() {
    // Setup phase (not profiled heavily)
    std::vector<int> v(1'000'000, 1);

    // Start of the "hot loop" we care about
    long long sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < v.size(); ++i) {
        sum += v[i];
    }

    std::cout << "Sum: " << sum << "\n";
    return 0;
}
