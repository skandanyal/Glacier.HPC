#include "openblas_kernel.h"
#include "openblas_parallel_kernel.h"
#include "parallel_kernel.h"
#include "parallel_restrict_kernel.h"
#include "plain_kernel.h"
#include "restrict_kernel.h"
#include "simd_kernel.h"

#include <gtest/gtest.h>
#include <vector>
#include "omp.h"
#include <immintrin.h>
#include <cblas.h>


// ---- 1. Correctness Test ---
TEST(SaxpyKernelTest, CorrectnessTest) {
    const int n = 100;
    const float a = 5.0f;
    std::vector<float> x(n);
    std::vector<float> y_opb(n);
    std::vector<float> y_opb_p(n);
    std::vector<float> y_par(n);
    std::vector<float> y_par_r(n);
    std::vector<float> y_pln(n);
    std::vector<float> y_rst(n);
    std::vector<float> y_simd(n);

    for (int i = 0; i < n; ++i) {
        x[i] = static_cast<float>(i);
        y_opb[i] = static_cast<float>(i);
        y_opb_p[i] = static_cast<float>(i);
        y_par[i] = static_cast<float>(i);
        y_par_r[i] = static_cast<float>(i);
        y_pln[i] = static_cast<float>(i);
        y_rst[i] = static_cast<float>(i);
        y_simd[i] = static_cast<float>(i);
    }

    saxpy_openblas(x.data(), y_opb.data(), a, n);
    saxpy_openblas_parallel(x.data(), y_opb_p.data(), a, n);
    saxpy_parallel(x.data(), y_par.data(), a, n);
    saxpy_parallel_restrict(x.data(), y_par_r.data(), a, n);
    saxpy_plain(x.data(), y_pln.data(), a, n);
    saxpy_restrict(x.data(), y_rst.data(), a, n);
    saxpy_simd(x.data(), y_simd.data(), a, n);

    for (int i = 0; i < n; ++i) {
        float expected = a * static_cast<float>(i) + static_cast<float>(i);
        EXPECT_FLOAT_EQ(y_opb[i], expected) << "saxpy_openblas mismatch at index " << i;
        EXPECT_FLOAT_EQ(y_opb_p[i], expected) << "saxpy_openblas_parallel mismatch at index " << i;
        EXPECT_FLOAT_EQ(y_par[i], expected) << "saxpy_parallel mismatch at index " << i;
        EXPECT_FLOAT_EQ(y_par_r[i], expected) << "saxpy_parallel_restrict mismatch at index " << i;
        EXPECT_FLOAT_EQ(y_pln[i], expected) << "saxpy_plain mismatch at index " << i;
        EXPECT_FLOAT_EQ(y_rst[i], expected) << "saxpy_restrict mismatch at index " << i;
        EXPECT_FLOAT_EQ(y_simd[i], expected) << "saxpy_simd mismatch at index " << i;
    }
}

// ---- 2. Shape Test ----
TEST(SaxpyKernelTest, ShapeTest) {
    const std::vector<int> test_shapes = {1, 7, 63, 1024, 65537};
    const float a = 3.5f;

    for (int n : test_shapes) {
        std::vector<float> x(n);
        std::vector<float> y_opb(n);
        std::vector<float> y_opb_p(n);
        std::vector<float> y_par(n);
        std::vector<float> y_par_r(n);
        std::vector<float> y_pln(n);
        std::vector<float> y_rst(n);
        std::vector<float> y_simd(n);

        for (int i = 0; i < n; ++i) {
            x[i] = static_cast<float>(i + 1);
            y_opb[i] = static_cast<float>((i + 1) * 2);
            y_opb_p[i] = static_cast<float>((i + 1) * 2);
            y_par[i] = static_cast<float>((i + 1) * 2);
            y_par_r[i] = static_cast<float>((i + 1) * 2);
            y_pln[i] = static_cast<float>((i + 1) * 2);
            y_rst[i] = static_cast<float>((i + 1) * 2);
            y_simd[i] = static_cast<float>((i + 1) * 2);
        }

        saxpy_openblas(x.data(), y_opb.data(), a, n);
        saxpy_openblas_parallel(x.data(), y_opb_p.data(), a, n);
        saxpy_parallel(x.data(), y_par.data(), a, n);
        saxpy_parallel_restrict(x.data(), y_par_r.data(), a, n);
        saxpy_plain(x.data(), y_pln.data(), a, n);
        saxpy_restrict(x.data(), y_rst.data(), a, n);
        saxpy_simd(x.data(), y_simd.data(), a, n);

        for (int i = 0; i < n; ++i) {
            float expected = a * static_cast<float>(i + 1) + static_cast<float>((i + 1) * 2);
            EXPECT_FLOAT_EQ(y_opb[i], expected) << "saxpy_openblas shape " << n << " mismatch at index " << i;
            EXPECT_FLOAT_EQ(y_opb_p[i], expected) << "saxpy_openblas_parallel shape " << n << " mismatch at index " << i;
            EXPECT_FLOAT_EQ(y_par[i], expected) << "saxpy_parallel shape " << n << " mismatch at index " << i;
            EXPECT_FLOAT_EQ(y_par_r[i], expected) << "saxpy_parallel_restrict shape " << n << " mismatch at index " << i;
            EXPECT_FLOAT_EQ(y_pln[i], expected) << "saxpy_plain shape " << n << " mismatch at index " << i;
            EXPECT_FLOAT_EQ(y_rst[i], expected) << "saxpy_restrict shape " << n << " mismatch at index " << i;
            EXPECT_FLOAT_EQ(y_simd[i], expected) << "saxpy_simd shape " << n << " mismatch at index " << i;
        }
    }
}
