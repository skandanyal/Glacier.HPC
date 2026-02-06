## Kernel: SAXPY

```
[y] = a*[x] + [y]

where:
- a = scalar constant
- [x], [y] = vectors
```

* FLOPs = 2 
* Arithmatic intensity = FLOPs / Bytes = 2 / 12 = 0.166

* FLOPs per iteration = FLOPs * iteration = 2 * total_number_of_rows_in_x(OR)y
* FLOPS per second = 2 * n / T  
* Memory Bandwidth in gbps = 12 * n / T / 1e9  
```


|                Attributes                 | `plain_kernel` | `restrict_kernel` | `parallel_kernel`<br>threads=1 | `parallel_kernel`<br>threads=2 | `parallel_kernel`<br>threads=3 | `parallel_kernel`<br>threads=4 | `gpu_kernel` |
|:-----------------------------------------:|:--------------:|:-----------------:|:------------------------------:|:------------------------------:|:------------------------------:|:------------------------------:|:------------:|
|                Iterations                 |      100       |        100        |              100               |              1000              |              1000              |              1000              |     1000     |
| Time taken per iteration `T`<br>(seconds) |    0.005033    |     0.012175      |            0.005154            |            0.004907            |    0.005122<br>mean of 10 exps |     0.005127<br>mean of 10 exps|              |
|          Instructions per Cycle           |      1.77      |       0.54        |              0.67              |              0.24              |              0.16              |               0.12             |              |
|           Frontend cycles idle            |     4.10%      |       4.28%       |             62.71%             |            72.28%              |             60.96%             |               55.18%           |              |
|          Memory bandwidth (GBps)          |     23.84      |       9.85        |             23.28              |             24.45              |             23.43              |               23.40            |              |
|             GFLOPs per second             |      3.97      |       1.64        |              3.88              |              4.08              |              3.91              |                3.90            |              |
|            Kernel overhead (%)            |     92.48%     |      91.56%       |             91.98%             |             97.76%             |              98.06%            |              98.48%            |              |
|               CPUs utilized               |     0.999      |       0.997       |             0.999              |             2.005              |              2.995             |              3.984             |              |


