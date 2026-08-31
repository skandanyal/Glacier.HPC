# Trial runs 
## SAXPY Benchmark Results    
Date: Friday, February 27, 2026    
Runs per configuration: 5    

| Kernel         | Threads | Time (s)     | GFLOPs/s | Mem BW (GB/s) | IPC   | Frontend Idle (%) | CPUs Utilized |
|----------------|---------|--------------|----------|---------------|-------|-------------------|---------------|
| saxpy_plain    | -       | 1.463800e-02 | 1.366    | 8.198         | 3.888 | 0.11              | 1.008         |
| saxpy_restrict | -       | 1.464300e-02 | 1.366    | 8.195         | 3.888 | 0.10              | 1.008         |
| saxpy_parallel | 1       | 1.349200e-02 | 1.482    | 8.894         | 4.065 | 0.10              | 1.009         |
| saxpy_parallel | 2       | 7.179000e-03 | 2.786    | 16.715        | 3.874 | 0.10              | 2.018         |
| saxpy_parallel | 4       | 5.116000e-03 | 3.909    | 23.456        | 2.811 | 0.18              | 4.034         |
| saxpy_parallel | 6       | 5.206000e-03 | 3.842    | 23.051        | 1.845 | 0.15              | 6.045         |


## SAXPY Benchmark Results    
Date: Sunday, March 01, 2026   
Runs per configuration: 5
    
|     Kernel     | Threads |   Time (s)   | GFLOPs/s | Mem BW (GB/s) |  IPC  | Frontend Idle (%) | CPUs Utilized |
|:--------------:|:-------:|:------------:|:--------:|:-------------:|:-----:|:-----------------:|:-------------:|
|  saxpy_plain   |    -    | 1.465600e-02 |  1.365   |     8.188     | 3.885 |       0.11        |     1.01      |
| saxpy_restrict |    -    | 1.463700e-02 |  1.366   |     8.199     | 3.888 |       0.11        |     1.01      |
| saxpy_parallel |    1    | 1.347900e-02 |  1.484   |     8.903     | 4.068 |       0.10        |     1.01      |
| saxpy_parallel |    2    | 7.158000e-03 |  2.794   |    16.765     | 3.884 |       0.11        |     2.02      |
| saxpy_parallel |    4    | 5.115000e-03 |  3.910   |    23.459     | 2.795 |       0.20        |     4.03      |
| saxpy_parallel |    6    | 5.200000e-03 |  3.846   |    23.078     | 1.843 |       0.18        |     6.05      |


# Final run 
## SAXPY Benchmark Results    
Date: Sunday, March 01, 2026   
Runs per configuration: 30
    
|     Kernel     | Threads |   Time (s)   | GFLOPs/s | Mem BW (GB/s) |  IPC  | Frontend Idle (%) | CPUs Utilized |
|:--------------:|:-------:|:------------:|:--------:|:-------------:|:-----:|:-----------------:|:-------------:|
|  saxpy_plain   |    -    | 1.472800e-02 |  1.358   |     8.148     | 3.881 |       0.10        |     1.01      |
| saxpy_restrict |    -    | 1.467700e-02 |  1.363   |     8.176     | 3.882 |       0.10        |     1.01      |
| saxpy_parallel |    1    | 1.354800e-02 |  1.476   |     8.857     | 4.059 |       0.11        |     1.01      |
| saxpy_parallel |    2    | 7.153500e-03 |  2.796   |    16.775     | 3.895 |       0.11        |     2.02      |
| saxpy_parallel |    4    | 5.052500e-03 |  3.958   |    23.752     | 2.903 |       0.18        |     4.03      |
| saxpy_parallel |    6    | 5.193500e-03 |  3.851   |    23.107     | 1.865 |       0.16        |     6.05      |


## Derived results 
Considering results obtained on March 01, 2026:
* Arithmatic Intensity = FLOPs/Bytes = 2/12 = 0.1667    
* P_peak = cores * freq * flops_per_cycle    
       = 6 * 4350 MHz * 32    
       = 835200 MFLOPs/s = 835.2 GFLOPs/s   
* Sustained memory bandwidth = 18.956 GB/s (memory roof) 
* P_memory = AI * BW_peak = 0.1667 * 18.956 = 3.159 GFLOPS/s (derived from STREAM suite)   
* P_compute (single precision) = 32 FLOPs / cycle / core     
                             = 32 * 4.35e9 * 6    
                             = 835 GFLOPs/s     
* AI_ridge = P_compute / BW_memory = 835 GFLOPs/s / 18.956 GB/s = 44 FLOPs/byte     
*Therefore, AI < 44 -> Memory bound (SAXPY)    
           AI > 44 -> Compute bound    


## Observation 
1. SAXPY is firmly situated in the `memory-bound` regime with Arithmatic Intensity of 0.1667 FLOPs/Byte.
A kernel would need to exceed the `44 FLOPs/Bytes` threashold to migrate into the `compute-bound` regime.
2. DRAM Memory Bandwidth as per:    
STREAM (Triad) benchmarking suit < Predicted peak < Observed peak (saxpy_parallel, threads=4)    
3.159 GFLOPs/s < 3.259 GFLOPs/s < 3.958 GFLOPs/s.
3. IPC (Instructions Per Cycle) drops as the kernel scales across threads.
4. Memory bandwidth saturates at 4 threads at around 23.7 GB/s, leading to Compute performance 
saturating at around 3.9 GFLOPs/s.
5. Using the `restrict` keyword did not result in any significnt change. Whereas the single 
threaded baseline with `restrict` and baseline + OpenMP thread count = 1 show minor but 
visible differences.
6. As speculated, using half the number of threads (6/12) resulted in the lowest time taken per 
1000 kernel runs, while bearing the expected drop in IPC, showcasing textbook `memory-bound` behaviour.
