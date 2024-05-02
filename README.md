# Parallel Bloom Filter
C implementation of Parallel Bloom Filter for gem5 simulation

## Compile
```
gcc -static ./src/bloom_filter.c -o ./bin/bloom_filter
```

## Test in gem5 and log metrics (paths may change)
```
build/X86/gem5.opt ./configs/project/bloom_simple.py >> ../../signatures/bloom_filter/gem5_metrics.txt
```