add_executable(gemm_test
        gemm_test.cpp
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/openblas_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/openblas_parallel_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/plain_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/plain_parallel_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/rearranged_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/rearranged_parallel_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/simd_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/strassen_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/strassen_parallel_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/tiled_kernel.c
        ${CMAKE_SOURCE_DIR}/src/gemm/kernels/tiled_parallel_kernel.c
)

target_include_directories(gemm_test PRIVATE ${CMAKE_SOURCE_DIR}/src/gemm/include)
target_compile_options(gemm_test PRIVATE -mavx2 -mfma)
target_link_libraries(gemm_test PRIVATE GTest::gtest_main project_config OpenMP::OpenMP_C BLAS::BLAS)

include(GoogleTest)
gtest_discover_tests(gemm_test)
