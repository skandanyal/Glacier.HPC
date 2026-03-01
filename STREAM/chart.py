import matplotlib.pyplot as plt 
import numpy as np


# data observed through experiment results mentioned in /STREAM/results/
threads = np.array([1,2,3,4,6,8,10,12])
bandwidth = np.array([17990.8, 18956.8, 18628.4, 18292.7, 17913.1, 17854.8, 17525.1, 17506.0])

bandwidth = np.array([i/1000.0 for i in bandwidth])

# generating plot using matplotlib 
plt.figure(figsize=(6,4), layout='constrained')

plt.plot(threads, 
         bandwidth, 
         marker='o')
plt.xlabel('Threads')
plt.ylabel('Memory bandwidth (GB/s)')
plt.title("Memory bandwidth on AMD Ryzen 5 6600H")
plt.title("Memory Bandwidth Scaling on Ryzen 5 6600H")
plt.grid()

plt.savefig("mem_bw.png", dpi=300)
