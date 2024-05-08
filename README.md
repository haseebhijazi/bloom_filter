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

## 10 addresses for signature
0x0000000000000000
0x1111111111111111
0x1010101010101010
0x1234123412341234
0x4321432143214321
0x3098587283749203
0x9874576374678237
0x1293984543735623
0x932846382a36528b
0xc74394a84394fff2