cmake_minimum_required(VERSION 3.20)
if (POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(Glacier.HPC LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(project_config INTERFACE)
target_compile_options(project_config INTERFACE
        -Wall -Wextra
        $<$<CONFIG:Debug>:-g -O0 -fopenmp -lopenblas -march=native>
        $<$<CONFIG:Benchmark>:-O3 -march=native -fopenmp -lopenblas -ffast-math>
)

find_package(OpenMP REQUIRED)
find_package(BLAS REQUIRED)

add_subdirectory(src/saxpy)


# ---- Fetched Google Test suit inside the VM upon every push ----
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)



#enable this when cuda is needed
#set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc CACHE FILEPATH "" FORCE)
#set(CMAKE_CUDA_ARCHITECTURES 86 CACHE STRING "" FORCE)
#
#project(Glacier.HPC LANGUAGES C CUDA)
