cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(Glacier.HPC LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(OpenMP REQUIRED)
find_package(BLAS REQUIRED)

# Interface target for project-wide flags & dependencies
add_library(project_config INTERFACE)

target_compile_options(project_config INTERFACE
        -Wall -Wextra
        -mavx2 -mfma
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Release>:-O3 -ffast-math>
        $<$<CONFIG:Benchmark>:-O3 -ffast-math -march=native>
)

# OpenMP and BLAS link properly across both C and CXX
target_link_libraries(project_config INTERFACE
        OpenMP::OpenMP_CXX
        BLAS::BLAS
)

# Source Kernels
add_subdirectory(src/saxpy)
add_subdirectory(src/gemm)

# Testing
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)