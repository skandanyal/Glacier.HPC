cmake_minimum_required(VERSION 3.20)

set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc CACHE FILEPATH "" FORCE)
set(CMAKE_CUDA_ARCHITECTURES 86 CACHE STRING "" FORCE)
project(Glacier.HPC C CXX CUDA)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CUDA_STANDARD 13)
set (CMAKE_CUDA_STANDARD_REQUIRED ON)

# Common flags for the whole project
add_library(project_config INTERFACE)
target_compile_options(project_config INTERFACE
        -Wall -Wextra
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Benchmark>:-O3 -march=native -fopenmp -ffast-math>
        $<$<CONFIG:CUDADebug>:-g>
        $<$<CONFIG:CUDABenchmark>:-g>
)

# Add kernel subdirectories here
add_subdirectory(src/saxpy)
add_subdirectory(src/squared_arr)