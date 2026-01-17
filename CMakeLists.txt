cmake_minimum_required(VERSION 4.0)
project(Glacier_HPC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -ffast-math -fopt-info-vec-optimized")

add_executable(Glacier_HPC main.cpp)

set(EIGEN_INCLUDE_DIR /home/skandan-c-y/cpp_libraries/eigen)

set(Boost_NO_SYSTEM_PATHS ON)
include_directories(BEFORE ${EIGEN_INCLUDE_DIR})
include_directories(BEFORE ${BOOST_INCLUDE_DIR})

find_package(OpenMP REQUIRED)
find_package(BLAS REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Glacier_HPC INTERFACE OpenMP::OpenMP_CXX)
endif()

if(BLAS_FOUND)
    target_link_libraries(Glacier_HPC INTERFACE BLAS::BLAS)
endif()

target_compile_definitions(Glacier_HPC PRIVATE Glacier_HPC)

target_compile_definitions(Glacier_HPC PRIVATE DEBUG_MODE=1)
