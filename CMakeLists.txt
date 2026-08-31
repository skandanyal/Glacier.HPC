cmake_minimum_required(VERSION 3.20)

project(Glacier.HPC LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(project_config INTERFACE)
target_compile_options(project_config INTERFACE
        -Wall -Wextra
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Benchmark>:-O3 -march=native -fopenmp -lopenblas -ffast-math -march=native>
)

find_package(OpenMP REQUIRED)
find_package(BLAS REQUIRED)

add_subdirectory(src/saxpy)



#enable this when cuda is needed
#set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc CACHE FILEPATH "" FORCE)
#set(CMAKE_CUDA_ARCHITECTURES 86 CACHE STRING "" FORCE)
#
#project(Glacier.HPC LANGUAGES C CUDA)
