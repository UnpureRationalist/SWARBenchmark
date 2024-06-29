# Performance comparison of popCount function

Test results:
```shell
2024-06-30T01:00:01+08:00
Running ./swarBenchmark
Run on (8 X 2500 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 4096 KiB (x8)
  L3 Unified 28160 KiB (x1)
Load Average: 0.10, 0.07, 0.11
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_RedisPopcount          3629826 ns      3629386 ns          192
BM_BasicPopCount         25606352 ns     25604317 ns           27
BM_BitAndPopCount        98210255 ns     98202993 ns            7
BM_GccBuiltinPopCount    36949327 ns     36947015 ns           19
BM_OpenmpBasicPopCount   14287040 ns     14286005 ns           49
```