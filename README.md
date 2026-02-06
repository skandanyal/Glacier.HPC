``` 
 ██████╗ ██╗      █████╗  ██████╗██╗███████╗██████╗    ██╗  ██╗██████╗  ██████╗
██╔════╝ ██║     ██╔══██╗██╔════╝██║██╔════╝██╔══██╗   ██║  ██║██╔══██╗██╔════╝
██║  ███╗██║     ███████║██║     ██║█████╗  ██████╔╝   ███████║██████╔╝██║     
██║   ██║██║     ██╔══██║██║     ██║██╔══╝  ██╔══██╗   ██╔══██║██╔═══╝ ██║     
╚██████╔╝███████╗██║  ██║╚██████╗██║███████╗██║  ██║██╗██║  ██║██║     ╚██████╗
 ╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝ 
 
Profiling, Benchmarking and Analysis of Numerical Kernels derived from common Supervised Machine Learning 
Algorithms on consumer grade computing hardware.   

Licensed for viewing only. Not open-source. See LICENSE.txt for details.      

Project scope: Major project for B.E CSE (AI&ML)
Author: Skandan C.Y                                       
```


## Goals
* Write clean, safe C17, C++20 with CMake as build system
* Study kernel behavior under different release configurations and compiler optimization flags
* Profile numerical kernels to identify behavior and system roofline
* Act as a controlled benchmarking environment to optimize numerical algorithms on Glacier.ML


## Non Goals
Glacier.HPC is not:
* A machine learning/deep learning framework 
* Open source or open to collaborations (yet)
* Full system profiling tool 
* Educational content 


## Scope 
Numerical kernels derived from common supervised machine learning algorithms, 
especially used in Glacier.ML
* SAXPY
* GEMM
* pth order distance (kNN)


## Benchmarking Environment
Benchmarks have been conducted on:
```
AMD Ryzen 6600H (6 cores / 12 threads)
```
Benchmark results are exploratory and used primarily for relative comparison and profiling, not for leaderboard claims.


## Languages and Frameworks used:
**Language:**
C++20, C17

**Core stack:**     
![C++](https://img.shields.io/badge/C++20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![C++](https://img.shields.io/badge/C17-00599C?style=for-the-badge&logo=c&logoColor=white)
![Eigen](https://img.shields.io/badge/Eigen3.0-1F1232?style=for-the-badge&logo=matrix&logoColor=white)
![OpenMP](https://img.shields.io/badge/OpenMP-26667F?style=for-the-badge&logo=openmp&logoColor=white)
![OpenBLAS](https://img.shields.io/badge/OpenBLAS-E00?style=for-the-badge&logo=openblas&logoColor=white)
![CUDA13](https://img.shields.io/badge/CUDA13-76B900?style=for-the-badge&logo=nvidia&logoColor=white)

**Development and Profiling:**       
![CMake](https://img.shields.io/badge/CMake-06466B?style=for-the-badge&logo=cmake&logoColor=white)
![perf](https://img.shields.io/badge/perf-E03C31?style=for-the-badge&logo=linux&logoColor=white)
![Nsight Compute](https://img.shields.io/badge/Nsight_Compute-76B900?style=for-the-badge&logo=nvidia&logoColor=white)



## Build instructions 🔨

To build with `release` flags (`-g`, `-O0`)
```
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Debug       
cmake --build cmake-build-release -j$(nproc)
```


## Status

```WORK IN PROGRESS```

* Benchmarking drivers, kernels and harnesses may change without notice
* This repository reflects an evolving understanding of performance-oriented kernel design.


## License

See `LICENSE`
