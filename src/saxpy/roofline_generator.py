import numpy as np
import matplotlib.pyplot as plt

# -----------------------------
# Machine Parameters
# -----------------------------
P_compute = 835        # GFLOPs/s (single precision peak)
BW_memory = 18.956     # GB/s (STREAM Triad peak)

# -----------------------------
# Kernel Data (SAXPY)
# -----------------------------
AI_saxpy = 0.1667      # FLOPs/byte
Perf_saxpy = 3.958     # GFLOPs/s (best measured)

# -----------------------------
# Roofline Construction
# -----------------------------
AI = np.logspace(-3, 3, 1000)

# Memory-bound line
memory_roof = BW_memory * AI

# Compute-bound ceiling
compute_roof = np.full_like(AI, P_compute)

# Actual roofline (min of both)
roofline = np.minimum(memory_roof, compute_roof)

# Ridge point
AI_ridge = P_compute / BW_memory

# -----------------------------
# Plot
# -----------------------------
plt.figure(figsize=(8,6))

plt.loglog(AI, memory_roof, linestyle='--', label='Memory Roof')
plt.loglog(AI, compute_roof, linestyle='--', label='Compute Roof')
plt.loglog(AI, roofline, linewidth=2, label='Roofline')

plt.scatter(AI_saxpy, Perf_saxpy)
plt.text(AI_saxpy, Perf_saxpy*1.2, "SAXPY")

plt.axvline(AI_ridge, linestyle=':', label=f'Ridge Point ≈ {AI_ridge:.1f}')

plt.xlabel('Arithmetic Intensity (FLOPs/Byte)')
plt.ylabel('Performance (GFLOPs/s)')
plt.title('Roofline Model – Ryzen 5 6600H')
plt.grid(True, which="both", ls="--")
plt.legend()

plt.tight_layout()
plt.savefig("roofline.png", dpi=300)
plt.show()
