#include "../include/parallel_kernel.h"

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
 * Wall-clock time
 * FLOPs/sec
 * Arithmetic intensity
 * Memory bandwidth
 * Vectorization reports
 * Scaling vs threads
 */

int main() {
  int n = 10000000;
  float *x = aligned_alloc(64, n * sizeof(float));
  float *y = aligned_alloc(64, n * sizeof(float));

  float a = 5.0f;

  for (int i = 0; i < n; i++) {
    x[i] = (float)i;
    y[i] = (float)i;
  }

  // heating the cache lines
  for (int i = 0; i < 5; i++) {
    saxpy_parallel(x, y, a, n);
  }

  // recording WALL-TIME
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  volatile float sink;

  // set number of threads
  omp_set_num_threads(omp_get_max_threads());

  // 1000 iterations for the parallel_kernel
  for (int i = 0; i < 1000; i++)
    saxpy_parallel(x, y, a, n);

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double total_time = ((end_time.tv_sec - start_time.tv_sec) +
                       (end_time.tv_nsec - start_time.tv_nsec) * 1e-9);
  double time_elapsed = total_time / 1000;

  // -----RESULTS-----
  sink = y[n - 1];
  int flops_per_iter = 2 * n;
  double flops_per_second = 2 * n / (float)time_elapsed;
  double mem_bandwidth_gbps = 12 * n / (float)time_elapsed / 1e9;

  printf("{");
  printf("\"kernel\":\"saxpy_parallel\",");
  printf("\"last_element\":%.6f,", sink);
  printf("\"mean_time_per_iteration\":%.6f,", time_elapsed);
  printf("\"flops_per_iter\":%d,", flops_per_iter);
  printf("\"flops_per_second\":%.6f,", flops_per_second);
  printf("\"memory_bandwidth_gbps\": %.6f}\n", mem_bandwidth_gbps);
  fflush(stdout);

  free(x);
  free(y);
  return 0;
}
