``` 
 ██████╗ ██╗      █████╗  ██████╗██╗███████╗██████╗    ██╗  ██╗██████╗  ██████╗
██╔════╝ ██║     ██╔══██╗██╔════╝██║██╔════╝██╔══██╗   ██║  ██║██╔══██╗██╔════╝
██║  ███╗██║     ███████║██║     ██║█████╗  ██████╔╝   ███████║██████╔╝██║     
██║   ██║██║     ██╔══██║██║     ██║██╔══╝  ██╔══██╗   ██╔══██║██╔═══╝ ██║     
╚██████╔╝███████╗██║  ██║╚██████╗██║███████╗██║  ██║██╗██║  ██║██║     ╚██████╗
 ╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝ 
 
Profiling, Benchmarking and Analysis of Numerical Kernels derived from common Supervised Machine Learning 
Algorithms on consumer grade computing hardware.    

Project scope: Major project for B.E CSE (AI&ML)
Author: Skandan C.Y                                       
```


## Goals
### Software and Runtime goals 
* Write clean, safe C17, C++20 with CMake as build system
* Study kernel behavior under different release configurations and compiler optimization flags
* Profile numerical kernels to identify behavior and system roofline
* Act as a controlled benchmarking environment to optimize numerical algorithms on Glacier.ML
### Research goals
* Study kernel behavior under iterative optimization techniques
* Study performance scaling across multiple threads 
* Finally, establish a roofline model depicting textbook vs observed kernel behaviour


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
### Manual performance settings 
* Laptop connected to power source
* Power mode set to `Performance`
* No other applications or background tasks opened manually

Benchmark results are exploratory and used primarily for relative comparison and profiling, not for leaderboard claims.


## Methodology
* Cache lines are heated before everytime the driver is run.
* Kernels are run 1000 times to ensure capture of coherent results.
* A Python based harness is used to perform benchmarking experiments, ensuring minimal human interference.


<-- ## Testing !-->
<-- ## Containerization and CI/CD pipeline !-->


## Languages and Frameworks used:
**Language:**
C++20, C17

**Core stack:**     
![Eigen](https://img.shields.io/badge/Eigen3.0-1F1232?style=for-the-badge&logo=matrix&logoColor=white)
![OpenMP](https://img.shields.io/badge/OpenMP-26667F?style=for-the-badge&logo=openmp&logoColor=white)
![OpenBLAS](https://img.shields.io/badge/OpenBLAS-E00?style=for-the-badge&logo=openblas&logoColor=white)
![CUDA13](https://img.shields.io/badge/CUDA13-76B900?style=for-the-badge&logo=nvidia&logoColor=white)

**Development and Profiling:**       
![CMake](https://img.shields.io/badge/CMake-06466B?style=for-the-badge&logo=cmake&logoColor=white)
![perf](https://img.shields.io/badge/perf-E03C31?style=for-the-badge&logo=linux&logoColor=white)
![Nsight Compute](https://img.shields.io/badge/Nsight_Compute-76B900?style=for-the-badge&logo=nvidia&logoColor=white)



## Build instructions 🔨

To build with `debug` flags (`-g`, `-O0`)
```bash
cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug       
cmake --build cmake-build-debud -j$(nproc)
```

To build with `release` flags (`-O3`, `-march=native`, `fopenmp`, `-ffast-math`)
```bash 
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release        
cmake --build cmake-build-release -j$(nproc)
```
