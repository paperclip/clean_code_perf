A response to https://www.computerenhance.com/p/clean-code-horrible-performance

I wanted to see what the code from the blog post would do on my machine, and investigate several alternative clean version could do.

| relative |            ns/shape |             shape/s |    err% |       ins/shape |       cyc/shape |    IPC |      bra/shape |   miss% |     total | benchmark
|---------:|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|   100.0% |                6.42 |      155,668,519.56 |    0.2% |           13.50 |           28.05 |  0.481 |           3.00 |   25.0% |      0.80 | `TotalAreaVTBL`
|   100.4% |                6.40 |      156,278,179.92 |    0.2% |           11.25 |           27.90 |  0.403 |           2.25 |   33.3% |      0.80 | `TotalAreaVTBL4`
|   121.0% |                5.31 |      188,375,335.58 |    0.1% |           13.25 |           23.24 |  0.570 |           4.00 |   19.1% |      0.66 | `TotalAreaSwitch`
|   122.9% |                5.23 |      191,348,412.17 |    0.2% |           11.19 |           22.86 |  0.489 |           3.44 |   22.2% |      0.65 | `TotalAreaSwitch4`
|   380.2% |                1.69 |      591,832,652.28 |    0.2% |            8.00 |            7.37 |  1.085 |           1.00 |    0.0% |      0.21 | `TotalAreaUnion`
|   377.6% |                1.70 |      587,788,528.74 |    0.3% |            4.75 |            7.42 |  0.640 |           0.25 |    0.0% |      0.21 | `TotalAreaUnion4`
|   113.2% |                5.67 |      176,212,454.64 |    0.1% |           13.25 |           24.78 |  0.535 |           4.00 |   19.1% |      0.70 | `TotalAreaSwitchPtr`
|   117.7% |                5.46 |      183,244,553.11 |    0.1% |           11.03 |           23.85 |  0.463 |           3.25 |   23.7% |      0.68 | `TotalAreaSwitchPtr4`
|    99.8% |                6.44 |      155,323,815.64 |    0.1% |           13.50 |           28.12 |  0.480 |           3.00 |   25.0% |      0.80 | `RawVector`
|    97.8% |                6.57 |      152,224,199.47 |    0.1% |           13.50 |           28.72 |  0.470 |           3.00 |   25.0% |      0.81 | `UniqueVector`
|   100.3% |                6.41 |      156,096,631.47 |    0.1% |           13.50 |           28.00 |  0.482 |           3.00 |   25.0% |      0.79 | `Shape Collection`
|   100.3% |                6.41 |      156,102,752.83 |    0.1% |           13.50 |           28.00 |  0.482 |           3.00 |   25.0% |      0.79 | `Accumulate`
|    94.2% |                6.82 |      146,644,371.07 |    0.1% |           11.50 |           29.79 |  0.386 |           3.00 |   25.0% |      0.85 | `Transform Parallel`
|    96.3% |                6.67 |      149,965,820.35 |    0.1% |           25.50 |           29.18 |  0.874 |           5.00 |   15.0% |      0.83 | `Variant Collection`
|   408.2% |                1.57 |      635,461,355.09 |    0.1% |            9.25 |            6.87 |  1.346 |           2.00 |    0.0% |      0.20 | `MultiCollection`
|   407.4% |                1.58 |      634,208,089.97 |    0.3% |            9.25 |            6.87 |  1.346 |           2.00 |    0.0% |      0.20 | `MultiCollectionTemplate`
|   407.8% |                1.58 |      634,876,311.02 |    0.3% |            9.25 |            6.87 |  1.346 |           2.00 |    0.0% |      0.20 | `MultiCollectionTemplateParallel`
|    58.4% |               11.00 |       90,938,416.79 |    0.5% |           13.50 |           47.92 |  0.282 |           3.00 |    0.0% |      1.37 | `SortedCollection`
|224,531,802.8% |                0.00 |349,525,333,333,333.38 |   40.0% |            0.00 |            0.00 |  0.490 |           0.00 |   10.0% |      0.01 | :wavy_dash: `Cached Collection` (Unstable with ~5.4 iters. Increase `minEpochIterations` to e.g. 54)

Elephants in the room
=====================

1. Most code in all programs, and all code in most programs is never bottle-necked on CPU performance, it is waiting for the network, or the disk, or the user.
Clean code is mostly about improving developer performance for that code, leaving time to do extra optimisation for the tiny minority of code where CPU efficiency matters.

2. A real work situation where Area() was needed multiple times for a static set of shapes would immediately suggest a cache - the caching version is so fast that nanobench can't cover it (last line in table)

Clean-ish approaches
====================

Most of the things I tried were not any better or worse:

* Using std::vector - allowing growing list of shapes
* Using std::vector and std::unique_ptr - avoiding manual memory management
* Using a custom class instead of directly managing vector/unique_ptr
* Using std::accumulate
* Using std::transform, in parallel mode
* Using variants

One approach was massively slower:

* sorting collection - I think this saves branch misses at the expense of jumping around memory.

One approach beat any of the unclean approaches:

* MultiCollection - storing each shape type in its own vector, that was 4x faster than the original, and faster than the TotalAreaUnion consistently.

Testing
=======

Tests were run on x86_64 under WSL.

3rd parties
===========

* nanobench - https://github.com/martinus/nanobench/releases/tag/v4.3.11
* Mersenne Twister - http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/index.html

Both MIT licenced.
