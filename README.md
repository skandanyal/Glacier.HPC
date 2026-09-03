from py_benchmark_harness import saxpy_benchmark

```
 ██████╗ ██╗      █████╗  ██████╗██╗███████╗██████╗    ██╗  ██╗██████╗  ██████╗
██╔════╝ ██║     ██╔══██╗██╔════╝██║██╔════╝██╔══██╗   ██║  ██║██╔══██╗██╔════╝
██║  ███╗██║     ███████║██║     ██║█████╗  ██████╔╝   ███████║██████╔╝██║
██║   ██║██║     ██╔══██║██║     ██║██╔══╝  ██╔══██╗   ██╔══██║██╔═══╝ ██║
╚██████╔╝███████╗██║  ██║╚██████╗██║███████╗██║  ██║██╗██║  ██║██║     ╚██████╗
 ╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝

Glacier.HPC: Profiling and benchmarking of numerical kernels from supervised machine learning
algorithms with emperical roofline analysis.

Project scope: Major project for B.E CSE (AI&ML)
Author: Skandan C.Y
```

**Language:**  
[![C](https://img.shields.io/badge/C-283593?style=for-the-badge&logo=c&logoColor=white)](https://www.c-language.org/)
[![C++20](https://img.shields.io/badge/C%2B%2B20-1565C0?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp/20)
[![Python 3.12](https://img.shields.io/badge/Python%203.12-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)

**Stack used:**  
![OpenMP](https://img.shields.io/badge/OpenMP-26667F?style=for-the-badge&logo=openmp&logoColor=white)
![OpenBLAS](https://img.shields.io/badge/OpenBLAS-E00?style=for-the-badge&logo=openblas&logoColor=white)

**Development, Profiling and Testing:**  
![CMake](https://img.shields.io/badge/CMake-06466B?style=for-the-badge&logo=cmake&logoColor=white)
![perf](https://img.shields.io/badge/perf-E03C31?style=for-the-badge&logo=linux&logoColor=white)
[![GTest](https://img.shields.io/badge/GTest-E03C31?style=for-the-badge&logo=gtest&logoColor=white)](https://github.com/google/googletest)
[![Glacier.ML CI](https://github.com/skandanyal/Glacier.HPC/actions/workflows/main.yml/badge.svg)](https://github.com/skandanyal/Glacier.HPC/actions/workflows/main.yml)

## Goals

### Software and Runtime goals

- Write clean, safe C17, C++20 with CMake as build system
- Study kernel behavior under different release configurations and compiler optimization flags
- Profile numerical kernels to identify behavior and system roofline
- Act as a controlled benchmarking environment to optimize numerical algorithms on [Glacier.ML](https://github.com/skandanyal/Glacier.ML/)

### Research goals

- Characterize the machine by establishing skeleton of roofline model
- Study kernel behavior under iterative optimization techniques
- Study performance scaling across multiple threads
- Finally, establish a roofline model depicting textbook vs observed kernel behaviour

---

## Scope

Numerical kernels derived from common supervised machine learning algorithms,
especially used in Glacier.ML

- SAXPY (roofline model established)agy
- GEMM
- pth order distance (kNN)

---

## Benchmarking Environment

Benchmarks have been conducted on:

```
AMD Ryzen 6600H (6 cores / 12 threads)
Future enhancements: NVidia RTX 3050
```

Refer `hardware_info.txt` for detailed information.

### Manual performance settings

- Laptop connected to power source
- Power mode set to `Performance`
- No other applications or background tasks opened manually

### Memory Bandwidth

Memory Bandwidth scaling across multiple threads was benchmarked using the original `Triad` kernel
from `STREAM` benchmarking suite. Peak Memory Bandwidth was found to be `18.956 GB/s` when set
to `threads=2`.
See `STREAM/README.md` for further infomation.

Theoretical bandwidth mentioned to be `38.4 GB/s`.

Benchmark results are exploratory and used primarily for relative comparison and profiling, not for leaderboard claims.

---

## Methodology

- Cache lines are heated before everytime the driver is run.
- Kernels are run 1000 times to ensure capture of coherent results.
- A Python based harness is used to perform benchmarking experiments, ensuring minimal human interference.
- Google Test suit is used to check for kernel correctness upon upload to version control.

---

## Languages and Frameworks used:

**Language:**  
[![C](https://img.shields.io/badge/C-283593?style=for-the-badge&logo=c&logoColor=white)](https://www.c-language.org/)
[![C++20](https://img.shields.io/badge/C%2B%2B20-1565C0?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp/20)
[![Python 3.12](https://img.shields.io/badge/Python%203.12-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)

**Stack used:**  
![OpenMP](https://img.shields.io/badge/OpenMP-26667F?style=for-the-badge&logo=openmp&logoColor=white)
![OpenBLAS](https://img.shields.io/badge/OpenBLAS-E00?style=for-the-badge&logo=openblas&logoColor=white)

**Development, Profiling and Testing:**  
![CMake](https://img.shields.io/badge/CMake-06466B?style=for-the-badge&logo=cmake&logoColor=white)
![perf](https://img.shields.io/badge/perf-E03C31?style=for-the-badge&logo=linux&logoColor=white)
[![GTest](https://img.shields.io/badge/GTest-E03C31?style=for-the-badge&logo=gtest&logoColor=white)](https://github.com/google/googletest)

---

## Build instructions

1. To build with `Debug` flags (`-g`, `-O0`)

```bash
cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-debud
```

2. To build with `Benchmark` flags (`-O3`, `-march=native`, `-ffast-math`)

```bash
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release
```

3. To build with `Release` flags (`-O3`, `-ffast-math`) {serves as CMakeLists' default fallback route}

```bash
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release
```

4. To generate and run `Tests`

```bash
cmake -S . -B cmake-build-test -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-test
ctest --test-dir cmake-build-test --output-on-failure
```

---

## To run the benchmark script

`Note:` Ensure that the binaries are build before running the following scripts

1. To benchmark the SAXPY binaries in `Debug` bin

```bash
python3 py_benchmark_harness/saxpy_benchmark.py --runs=5 --bin=debug
```

2. To benchmark the SAXPY binaries in `Benchmark` bin

```bash
python3 py_benchmark_harness/saxpy_benchmark.py --runs=30 --bin=benchmark
```

3. To benchmark the GEMM binaries in `Debug` bin

```bash
python3 py_benchmark_harness/gemm_benchmark.py --runs=5 --bin=debug
```

4. To benchmark the GEMM binaries in `Benchmark` bin

```bash
python3 py_benchmark_harness/gemm_benchmark.py --runs=30 --bin=benchmark
```
