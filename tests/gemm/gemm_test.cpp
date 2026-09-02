#include "openblas_kerenl.h"
#include "openblas_parallel_kerenl.h"
#include "plain_kernel.h"
#include "plain_parallel_kernel.h"
#include "rearranged_kernel.h"
#include "rearranged_parallel_kernel.h"
#include "simd_kernel.h"
#include "strassen_kernel.h"
#include "strassen_parallel_kernel.h"
#include "tiled_kernel.h"
#include "tiled_parallel_kernel.h"

#include <gtest/gtest.h>
#include <vector>
#include <cmath>

static float compute_expected(int i, int j, int cA) {
    float sum = 0.0f;
    for (int k = 0; k < cA; ++k) {
        sum += static_cast<float>(i + k + 1) * static_cast<float>(k + j + 1);
    }
    return sum;
}

// ---- 1. Correctness Test ----
TEST(GemmKernelTest, CorrectnessTest) {
    const int rA = 16, cA = 16, cB = 16;
    std::vector<float> A(rA * cA);
    std::vector<float> B(cA * cB);

    for (int i = 0; i < rA; ++i) {
        for (int k = 0; k < cA; ++k) {
            A[i * cA + k] = static_cast<float>(i + k + 1);
        }
    }
    for (int k = 0; k < cA; ++k) {
        for (int j = 0; j < cB; ++j) {
            B[k * cB + j] = static_cast<float>(k + j + 1);
        }
    }

    std::vector<float> C_pln(rA * cB, 0.0f);
    std::vector<float> C_pln_p(rA * cB, 0.0f);
    std::vector<float> C_rea(rA * cB, 0.0f);
    std::vector<float> C_rea_p(rA * cB, 0.0f);
    std::vector<float> C_tld(rA * cB, 0.0f);
    std::vector<float> C_tld_p(rA * cB, 0.0f);
    std::vector<float> C_str(rA * cB, 0.0f);
    std::vector<float> C_str_p(rA * cB, 0.0f);
    std::vector<float> C_simd(rA * cB, 0.0f);
    std::vector<float> C_opb(rA * cB, 0.0f);
    std::vector<float> C_opb_p(rA * cB, 0.0f);

    gemm_plain(A.data(), B.data(), C_pln.data(), rA, cA, cB);
    gemm_plain_parallel(A.data(), B.data(), C_pln_p.data(), rA, cA, cB);
    gemm_rearranged(A.data(), B.data(), C_rea.data(), rA, cA, cB);
    gemm_rearranged_parallel(A.data(), B.data(), C_rea_p.data(), rA, cA, cB);
    gemm_tiled(A.data(), B.data(), C_tld.data(), rA, cA, cB);
    gemm_tiled_parallel(A.data(), B.data(), C_tld_p.data(), rA, cA, cB);
    gemm_strassen(A.data(), B.data(), C_str.data(), rA, cA, cB);
    gemm_strassen_parallel(A.data(), B.data(), C_str_p.data(), rA, cA, cB);
    gemm_simd(A.data(), B.data(), C_simd.data(), rA, cA, cB);
    gemm_openblas(A.data(), B.data(), C_opb.data(), rA, cA, cB);
    gemm_openblas_parallel(A.data(), B.data(), C_opb_p.data(), rA, cA, cB);

    for (int i = 0; i < rA; ++i) {
        for (int j = 0; j < cB; ++j) {
            float exp = compute_expected(i, j, cA);
            int idx = i * cB + j;
            EXPECT_NEAR(C_pln[idx], exp, 1e-3f) << "gemm_plain mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_pln_p[idx], exp, 1e-3f) << "gemm_plain_parallel mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_rea[idx], exp, 1e-3f) << "gemm_rearranged mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_rea_p[idx], exp, 1e-3f) << "gemm_rearranged_parallel mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_tld[idx], exp, 1e-3f) << "gemm_tiled mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_tld_p[idx], exp, 1e-3f) << "gemm_tiled_parallel mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_str[idx], exp, 1e-3f) << "gemm_strassen mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_str_p[idx], exp, 1e-3f) << "gemm_strassen_parallel mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_simd[idx], exp, 1e-3f) << "gemm_simd mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_opb[idx], exp, 1e-3f) << "gemm_openblas mismatch at (" << i << "," << j << ")";
            EXPECT_NEAR(C_opb_p[idx], exp, 1e-3f) << "gemm_openblas_parallel mismatch at (" << i << "," << j << ")";
        }
    }
}

// ---- 2. Shape Test ----
TEST(GemmKernelTest, ShapeTest) {
    struct MatrixShape { int rA, cA, cB; };
    const std::vector<MatrixShape> test_shapes = {
        {1, 1, 1},
        {4, 4, 4},
        {8, 8, 8},
        {32, 32, 32},
        {64, 64, 64},
        {3, 5, 7}
    };

    for (const auto& shape : test_shapes) {
        int rA = shape.rA, cA = shape.cA, cB = shape.cB;
        std::vector<float> A(rA * cA);
        std::vector<float> B(cA * cB);

        for (int i = 0; i < rA; ++i) {
            for (int k = 0; k < cA; ++k) {
                A[i * cA + k] = static_cast<float>(i + k + 1);
            }
        }
        for (int k = 0; k < cA; ++k) {
            for (int j = 0; j < cB; ++j) {
                B[k * cB + j] = static_cast<float>(k + j + 1);
            }
        }

        std::vector<float> C_pln(rA * cB, 0.0f);
        std::vector<float> C_pln_p(rA * cB, 0.0f);
        std::vector<float> C_rea(rA * cB, 0.0f);
        std::vector<float> C_rea_p(rA * cB, 0.0f);
        std::vector<float> C_tld(rA * cB, 0.0f);
        std::vector<float> C_tld_p(rA * cB, 0.0f);
        std::vector<float> C_str(rA * cB, 0.0f);
        std::vector<float> C_str_p(rA * cB, 0.0f);
        std::vector<float> C_simd(rA * cB, 0.0f);
        std::vector<float> C_opb(rA * cB, 0.0f);
        std::vector<float> C_opb_p(rA * cB, 0.0f);

        gemm_plain(A.data(), B.data(), C_pln.data(), rA, cA, cB);
        gemm_plain_parallel(A.data(), B.data(), C_pln_p.data(), rA, cA, cB);
        gemm_rearranged(A.data(), B.data(), C_rea.data(), rA, cA, cB);
        gemm_rearranged_parallel(A.data(), B.data(), C_rea_p.data(), rA, cA, cB);
        gemm_tiled(A.data(), B.data(), C_tld.data(), rA, cA, cB);
        gemm_tiled_parallel(A.data(), B.data(), C_tld_p.data(), rA, cA, cB);
        gemm_strassen(A.data(), B.data(), C_str.data(), rA, cA, cB);
        gemm_strassen_parallel(A.data(), B.data(), C_str_p.data(), rA, cA, cB);
        gemm_simd(A.data(), B.data(), C_simd.data(), rA, cA, cB);
        gemm_openblas(A.data(), B.data(), C_opb.data(), rA, cA, cB);
        gemm_openblas_parallel(A.data(), B.data(), C_opb_p.data(), rA, cA, cB);

        for (int i = 0; i < rA; ++i) {
            for (int j = 0; j < cB; ++j) {
                float exp = compute_expected(i, j, cA);
                int idx = i * cB + j;
                EXPECT_NEAR(C_pln[idx], exp, 1e-3f) << "gemm_plain shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_pln_p[idx], exp, 1e-3f) << "gemm_plain_parallel shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_rea[idx], exp, 1e-3f) << "gemm_rearranged shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_rea_p[idx], exp, 1e-3f) << "gemm_rearranged_parallel shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_tld[idx], exp, 1e-3f) << "gemm_tiled shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_tld_p[idx], exp, 1e-3f) << "gemm_tiled_parallel shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_str[idx], exp, 1e-3f) << "gemm_strassen shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_str_p[idx], exp, 1e-3f) << "gemm_strassen_parallel shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_simd[idx], exp, 1e-3f) << "gemm_simd shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_opb[idx], exp, 1e-3f) << "gemm_openblas shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
                EXPECT_NEAR(C_opb_p[idx], exp, 1e-3f) << "gemm_openblas_parallel shape (" << rA << "," << cA << "," << cB << ") mismatch at (" << i << "," << j << ")";
            }
        }
    }
}
