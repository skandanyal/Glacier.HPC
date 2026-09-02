#include "../include/simd_kernel.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int rA = 512, cA = 512, cB = 512;
  float *A = (float *)aligned_alloc(64, rA * cA * sizeof(float));
  float *B = (float *)aligned_alloc(64, cA * cB * sizeof(float));
  float *C = (float *)aligned_alloc(64, rA * cB * sizeof(float));

  for (int i = 0; i < rA * cA; i++) A[i] = 1.0f;
  for (int i = 0; i < cA * cB; i++) B[i] = 1.0f;
  for (int i = 0; i < rA * cB; i++) C[i] = 0.0f;

  for (int i = 0; i < 5; i++) {
    gemm_simd(A, B, C, rA, cA, cB);
  }

  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  volatile float sink;

  for (int i = 0; i < 10; i++)
    gemm_simd(A, B, C, rA, cA, cB);

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double time_elapsed = ((end_time.tv_sec - start_time.tv_sec) +
                         (end_time.tv_nsec - start_time.tv_nsec) * 1e-9);
  double time_per_iteration = time_elapsed / 10.0;

  sink = C[rA * cB - 1];
  long long flops_per_iter = 2LL * rA * cA * cB;
  double flops_per_second = (double)flops_per_iter / time_per_iteration;
  double mem_bandwidth_gbps = (3.0 * rA * cB * sizeof(float)) / time_per_iteration / 1e9;

  printf("{");
  printf("\"kernel\":\"gemm_simd\",");
  printf("\"last_element\":%.6f,", sink);
  printf("\"mean_time_per_iteration\":%.6f,", time_per_iteration);
  printf("\"flops_per_iter\":%lld,", flops_per_iter);
  printf("\"flops_per_second\":%.6f,", flops_per_second);
  printf("\"memory_bandwidth_gbps\": %.6f}\n", mem_bandwidth_gbps);
  fflush(stdout);

  free(A);
  free(B);
  free(C);
  return 0;
}
