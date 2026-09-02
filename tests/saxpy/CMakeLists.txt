add_executable(saxpy_test
        saxpy_test.cpp
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/openblas_kernel.c
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/openblas_parallel_kernel.c
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/parallel_kernel.c
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/parallel_restrict_kernel.c
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/plain_kernel.c
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/restrict_kernel.c
        ${CMAKE_SOURCE_DIR}/src/saxpy/kernels/simd_kernel.c
)

target_include_directories(saxpy_test PRIVATE ${CMAKE_SOURCE_DIR}/src/saxpy/include)
target_compile_options(saxpy_test PRIVATE -mavx2 -mfma)
target_link_libraries(saxpy_test PRIVATE GTest::gtest_main project_config OpenMP::OpenMP_C BLAS::BLAS)

include(GoogleTest)
gtest_discover_tests(saxpy_test)
