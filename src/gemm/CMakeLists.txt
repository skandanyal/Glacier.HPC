# Serial Plain
add_executable(gemm_plain
        driver/plain_driver.c
        kernels/plain_kernel.c
)
target_link_libraries(gemm_plain PRIVATE project_config)
target_include_directories(gemm_plain PRIVATE .)

# Plain Parallel
add_executable(gemm_plain_parallel
        driver/plain_parallel_driver.c
        kernels/plain_parallel_kernel.c
)
target_link_libraries(gemm_plain_parallel PRIVATE project_config OpenMP::OpenMP_C)
target_include_directories(gemm_plain_parallel PRIVATE .)

# Rearranged
add_executable(gemm_rearranged
        driver/rearranged_driver.c
        kernels/rearranged_kernel.c
)
target_link_libraries(gemm_rearranged PRIVATE project_config)
target_include_directories(gemm_rearranged PRIVATE .)

# Rearranged Parallel
add_executable(gemm_rearranged_parallel
        driver/rearranged_parallel_driver.c
        kernels/rearranged_parallel_kernel.c
)
target_link_libraries(gemm_rearranged_parallel PRIVATE project_config OpenMP::OpenMP_C)
target_include_directories(gemm_rearranged_parallel PRIVATE .)

# Tiled
add_executable(gemm_tiled
        driver/tiled_driver.c
        kernels/tiled_kernel.c
)
target_link_libraries(gemm_tiled PRIVATE project_config)
target_include_directories(gemm_tiled PRIVATE .)

# Tiled Parallel
add_executable(gemm_tiled_parallel
        driver/tiled_parallel_driver.c
        kernels/tiled_parallel_kernel.c
)
target_link_libraries(gemm_tiled_parallel PRIVATE project_config OpenMP::OpenMP_C)
target_include_directories(gemm_tiled_parallel PRIVATE .)

# Strassen
add_executable(gemm_strassen
        driver/strassen_driver.c
        kernels/strassen_kernel.c
)
target_link_libraries(gemm_strassen PRIVATE project_config)
target_include_directories(gemm_strassen PRIVATE .)

# Strassen Parallel
add_executable(gemm_strassen_parallel
        driver/strassen_parallel_driver.c
        kernels/strassen_parallel_kernel.c
)
target_link_libraries(gemm_strassen_parallel PRIVATE project_config OpenMP::OpenMP_C)
target_include_directories(gemm_strassen_parallel PRIVATE .)

# SIMD
add_executable(gemm_simd
        driver/simd_driver.c
        kernels/simd_kernel.c
)
target_compile_options(gemm_simd PRIVATE -mavx2 -mfma)
target_link_libraries(gemm_simd PRIVATE project_config)
target_include_directories(gemm_simd PRIVATE .)

# OpenBLAS
add_executable(gemm_openblas
        driver/openblas_driver.c
        kernels/openblas_kernel.c
)
target_link_libraries(gemm_openblas PRIVATE project_config BLAS::BLAS)
target_include_directories(gemm_openblas PRIVATE .)

# OpenBLAS Parallel
add_executable(gemm_openblas_parallel
        driver/openblas_parallel_driver.c
        kernels/openblas_parallel_kernel.c
)
target_link_libraries(gemm_openblas_parallel PRIVATE project_config BLAS::BLAS)
target_include_directories(gemm_openblas_parallel PRIVATE .)

