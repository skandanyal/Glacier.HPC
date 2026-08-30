# -------------------------
# Serial
# -------------------------
add_executable(saxpy_plain
        driver/plain_driver.c
        kernels/plain_kernel.c
)
target_link_libraries(saxpy_plain PRIVATE project_config)
target_include_directories(saxpy_plain PRIVATE .)

# -------------------------
# Restrict
# -------------------------
add_executable(saxpy_restrict
        driver/restrict_driver.c
        kernels/restrict_kernel.c
)
target_link_libraries(saxpy_restrict PRIVATE project_config)
target_include_directories(saxpy_restrict PRIVATE .)

# -------------------------
# OpenMP
# -------------------------
add_executable(saxpy_parallel
        driver/parallel_driver.c
        kernels/parallel_kernel.c
)
target_link_libraries(saxpy_parallel PRIVATE project_config OpenMP::OpenMP_C)
target_include_directories(saxpy_parallel PRIVATE .)

# -------------------------
# CUDA
# -------------------------
#add_executable(saxpy_gpu
#        driver/gpu_driver.c
#        kernels/gpu_kernel.cu
#)
#target_link_libraries(saxpy_gpu PRIVATE project_config cuda)
#target_include_directories(saxpy_gpu PRIVATE .)
#
#set_target_properties(saxpy_gpu PROPERTIES
#        CUDA_SEPARABLE_COMPILATION ON
#)
