#include "../include/strassen_kernel.h"
#include <stdlib.h>

static void add_matrix(const float *A, const float *B, float *C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] + B[i];
}

static void sub_matrix(const float *A, const float *B, float *C, int n) {
    for (int i = 0; i < n * n; i++) C[i] = A[i] - B[i];
}

static void strassen_rec(const float *A, const float *B, float *C, int n) {
    if (n <= 32) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                float a = A[i * n + k];
                for (int j = 0; j < n; j++) {
                    C[i * n + j] += a * B[k * n + j];
                }
            }
        }
        return;
    }

    int half = n / 2;
    int size = half * half;

    float *A11 = (float *)malloc(size * sizeof(float));
    float *A12 = (float *)malloc(size * sizeof(float));
    float *A21 = (float *)malloc(size * sizeof(float));
    float *A22 = (float *)malloc(size * sizeof(float));
    float *B11 = (float *)malloc(size * sizeof(float));
    float *B12 = (float *)malloc(size * sizeof(float));
    float *B21 = (float *)malloc(size * sizeof(float));
    float *B22 = (float *)malloc(size * sizeof(float));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i * half + j] = A[i * n + j];
            A12[i * half + j] = A[i * n + j + half];
            A21[i * half + j] = A[(i + half) * n + j];
            A22[i * half + j] = A[(i + half) * n + j + half];

            B11[i * half + j] = B[i * n + j];
            B12[i * half + j] = B[i * n + j + half];
            B21[i * half + j] = B[(i + half) * n + j];
            B22[i * half + j] = B[(i + half) * n + j + half];
        }
    }

    float *S1 = (float *)calloc(size, sizeof(float));
    float *S2 = (float *)calloc(size, sizeof(float));
    float *M1 = (float *)calloc(size, sizeof(float));
    float *M2 = (float *)calloc(size, sizeof(float));
    float *M3 = (float *)calloc(size, sizeof(float));
    float *M4 = (float *)calloc(size, sizeof(float));
    float *M5 = (float *)calloc(size, sizeof(float));
    float *M6 = (float *)calloc(size, sizeof(float));
    float *M7 = (float *)calloc(size, sizeof(float));

    add_matrix(A11, A22, S1, half);
    add_matrix(B11, B22, S2, half);
    strassen_rec(S1, S2, M1, half);

    add_matrix(A21, A22, S1, half);
    strassen_rec(S1, B11, M2, half);

    sub_matrix(B12, B22, S2, half);
    strassen_rec(A11, S2, M3, half);

    sub_matrix(B21, B11, S2, half);
    strassen_rec(A22, S2, M4, half);

    add_matrix(A11, A12, S1, half);
    strassen_rec(S1, B22, M5, half);

    sub_matrix(A21, A11, S1, half);
    add_matrix(B11, B12, S2, half);
    strassen_rec(S1, S2, M6, half);

    sub_matrix(A12, A22, S1, half);
    add_matrix(B21, B22, S2, half);
    strassen_rec(S1, S2, M7, half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int idx = i * half + j;
            C[i * n + j] += M1[idx] + M4[idx] - M5[idx] + M7[idx];
            C[i * n + j + half] += M3[idx] + M5[idx];
            C[(i + half) * n + j] += M2[idx] + M4[idx];
            C[(i + half) * n + j + half] += M1[idx] - M2[idx] + M3[idx] + M6[idx];
        }
    }

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(S1); free(S2);
    free(M1); free(M2); free(M3); free(M4); free(M5); free(M6); free(M7);
}

void gemm_strassen(const float *A, const float *B, float *C, int rA, int cA, int cB) {
    if (rA == cA && cA == cB && (rA & (rA - 1)) == 0) {
        strassen_rec(A, B, C, rA);
    } else {
        for (int i = 0; i < rA; i++) {
            for (int k = 0; k < cA; k++) {
                float a = A[i * cA + k];
                for (int j = 0; j < cB; j++) {
                    C[i * cB + j] += a * B[k * cB + j];
                }
            }
        }
    }
}
