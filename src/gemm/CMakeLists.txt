#-------------------------- 
# gemm step1 
# -------------------------
add_executable(gs1 
        driver/gemm_step1.c
        kernels/gemm_step1.c
)
target_link_libraries(gs1 PRIVATE project_config)
target_include_directories(gs1 PRIVATE .)

# -------------------------
# gemm step2 
# -------------------------
add_executable(gs2 
        driver/gemm_step2.c
        kernels/gemm_step2.c
)
target_link_libraries(gs2 PRIVATE project_config)
target_include_directories(gs2 PRIVATE .)

