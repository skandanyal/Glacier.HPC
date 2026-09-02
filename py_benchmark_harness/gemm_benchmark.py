import subprocess
import json
import statistics
from datetime import datetime
import os
import argparse


# -- inputs --
parser = argparse.ArgumentParser(description="Enter the number of runs and binary build location.")

parser.add_argument('--runs', type=int, required=True, help="Number of runs")
parser.add_argument('--bin', type=str, choices=["debug", "benchmark"], required=True, help="Binary build location ('debug' or 'benchmark'")
args = parser.parse_args()

if args.bin == "benchmark" and args.runs < 5:
    raise RuntimeError("Minimum accepted runs for benchmark are 5.")
if args.runs < 1:
    raise RuntimeError("Minimum accepted runs are 1.")


# -- defining binaries in their bins --
benchmark_binaries_debug = {
    "gemm_plain": "./cmake-build-debug/src/gemm/gemm_plain",
    "gemm_plain_parallel": "./cmake-build-debug/src/gemm/gemm_plain_parallel",
    "gemm_rearranged": "./cmake-build-debug/src/gemm/gemm_rearranged",
    "gemm_rearranged_parallel": "./cmake-build-debug/src/gemm/gemm_rearranged_parallel",
    "gemm_tiled": "./cmake-build-debug/src/gemm/gemm_tiled",
    "gemm_tiled_parallel": "./cmake-build-debug/src/gemm/gemm_tiled_parallel",
    "gemm_strassen": "./cmake-build-debug/src/gemm/gemm_strassen",
    "gemm_strassen_parallel": "./cmake-build-debug/src/gemm/gemm_strassen_parallel",
    "gemm_openblas": "./cmake-build-debug/src/gemm/gemm_openblas",
    "gemm_openblas_parallel": "./cmake-build-debug/src/gemm/gemm_openblas_parallel",
    "gemm_simd": "./cmake-build-debug/src/gemm/gemm_simd",
    "gemm_parallel": "./cmake-build-debug/src/gemm/gemm_parallel",
}

benchmark_binaries_benchmark = {
    "gemm_plain": "./cmake-build-benchmark/src/gemm/gemm_plain",
    "gemm_plain_parallel": "./cmake-build-benchmark/src/gemm/gemm_plain_parallel",
    "gemm_rearranged": "./cmake-build-benchmark/src/gemm/gemm_rearranged",
    "gemm_rearranged_parallel": "./cmake-build-benchmark/src/gemm/gemm_rearranged_parallel",
    "gemm_tiled": "./cmake-build-benchmark/src/gemm/gemm_tiled",
    "gemm_tiled_parallel": "./cmake-build-benchmark/src/gemm/gemm_tiled_parallel",
    "gemm_strassen": "./cmake-build-benchmark/src/gemm/gemm_strassen",
    "gemm_strassen_parallel": "./cmake-build-benchmark/src/gemm/gemm_strassen_parallel",
    "gemm_openblas": "./cmake-build-benchmark/src/gemm/gemm_openblas",
    "gemm_openblas_parallel": "./cmake-build-benchmark/src/gemm/gemm_openblas_parallel",
    "gemm_simd": "./cmake-build-benchmark/src/gemm/gemm_simd",
    "gemm_parallel": "./cmake-build-benchmark/src/gemm/gemm_parallel",
}


runs = args.runs
parallel_thread_counts = [1, 2, 4, 6]
physical_cores = [0, 2, 4, 6, 8, 10]

benchmark_binaries = {}
if args.bin == "debug":
    benchmark_binaries = benchmark_binaries_debug
elif args.bin == "benchmark":
    benchmark_binaries = benchmark_binaries_benchmark

perf_events = [
    "cycles",
    "instructions",
    "cache-misses",
    "cache-references",
    "stalled-cycles-frontend",
    "task-clock"
]


def run_perf(binary, threads=None):
    env = os.environ.copy()
    cmd = []

    if threads is not None:
        env["OMP_NUM_THREADS"] = str(threads)
        env["OPENBLAS_NUM_THREADS"] = str(threads)
        env["OMP_PROC_BIND"] = "true"
        env["OMP_PLACES"] = "cores"
        core_list = ",".join(map(str, physical_cores[:threads]))
        cmd.extend(["taskset", "-c", core_list])

    cmd.extend([
        "perf", "stat",
        "--all-user",
        "-x,", "-e", ",".join(perf_events),
        binary
    ])

    json_outputs = []
    perf_outputs = []

    for _ in range(runs):
        proc = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            env=env
        )


        print("STDOUT:", repr(proc.stdout))
        print("STDERR:", repr(proc.stderr))

        json_outputs.append(json.loads(proc.stdout))
        perf_outputs.append(proc.stderr.strip())

    return json_outputs, perf_outputs


def parse_perf(perf_text):
    metrics = {}

    for line in perf_text.splitlines():
        parts = line.split(",")
        if len(parts) < 3:
            continue

        raw_value = parts[0].replace(",", "").strip()
        event = parts[2].strip()

        try:
            value = float(raw_value)
            metrics[event] = value
        except:
            continue

    return metrics


def median(lst):
    return statistics.median(lst)


results = {}

for name, binary in benchmark_binaries.items():

    parallel_kernels = ["gemm_parallel", "gemm_openblas_parallel", "gemm_plain_parallel", "gemm_rearranged_parallel", "gemm_tiled_parallel", "gemm_strassen_parallel"]
    thread_list = parallel_thread_counts if name in parallel_kernels else [None]

    for t in thread_list:
        key = f"{name}" + (f"_threads{t}" if t else "")

        times = []
        gflops_list = []
        bandwidths = []
        ipc_list = []
        frontend_idle_pct = []
        cpus_utilized = []

        json_runs, perf_runs = run_perf(binary, threads=t)

        for j_out, p_out in zip(json_runs, perf_runs):

            # JSON
            time_s = j_out["mean_time_per_iteration"]
            flops_iter = j_out["flops_per_iter"]

            times.append(time_s)
            gflops_list.append(flops_iter / time_s / 1e9)
            bandwidths.append(j_out["memory_bandwidth_gbps"])

            # PERF
            perf = parse_perf(p_out)

            cycles = perf.get("cycles", 1)
            instructions = perf.get("instructions", 1)
            stalled_frontend = perf.get("stalled-cycles-frontend", 0)
            task_clock_ms = perf.get("task-clock", 0)

            ipc_list.append(instructions / cycles)

            frontend_idle_pct.append(
                100.0 * stalled_frontend / cycles
            )

            # CPUs utilized
            cpus_utilized.append((task_clock_ms / 1000.0) / time_s / 1000.0)

        results[key] = {
            "median_time": median(times),
            "median_gflops": median(gflops_list),
            "median_bandwidth": median(bandwidths),
            "median_ipc": median(ipc_list),
            "median_frontend_idle": median(frontend_idle_pct),
            "median_cpus_utilized": median(cpus_utilized),
            "lowest_time_taken": min(times),
            "highest_time_taken": max(times),
        }


now = datetime.now().strftime("%A, %B %d, %Y")

print(f"## GEMM Benchmark Results    ")
print(f"Date: {now}   ")
print(f"Runs per configuration: {runs}\n    ")
print(f"Configuration: {args.bin}\n    ")

print("| Kernel | Threads | Median time (s) | Highest time (s) | Lowest time(s) | GFLOPs/s | Mem BW (GB/s) | IPC | Frontend Idle (%) | CPUs Utilized |")
print("|:------:|:-------:|:---------------:|:----------------:|:--------------:|:--------:|:-------------:|:---:|:-----------------:|:-------------:|")

for k, v in results.items():
    if "_threads" in k:
        base_name, threads = k.split("_threads")
    else:
        base_name = k
        threads = "-"

    print(
        f"| {base_name} | {threads} | "
        f"{v['median_time']:.6e} | "
        f"{v['highest_time_taken']:.6e} | "
        f"{v['lowest_time_taken']:.6e} | "
        f"{v['median_gflops']:.3f} | "
        f"{v['median_bandwidth']:.3f} | "
        f"{v['median_ipc']:.3f} | "
        f"{v['median_frontend_idle']:.2f} | "
        f"{v['median_cpus_utilized']:.2f} | "
    )
