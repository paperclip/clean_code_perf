A response to https://www.computerenhance.com/p/clean-code-horrible-performance

I wanted to see what the code from the blog post would do on my machine, and investigate several alternative clean version could do.

| relative |            ns/shape |             shape/s |    err% |       ins/shape |       cyc/shape |    IPC |      bra/shape |   miss% |     total | benchmark
|---------:|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|   100.0% |                6.52 |      153,263,813.66 |    0.0% |           13.50 |           28.50 |  0.474 |           3.00 |   25.0% |      4.08 | `TotalAreaVTBL`
|   101.0% |                6.46 |      154,793,340.64 |    0.1% |           11.25 |           28.21 |  0.399 |           2.25 |   33.2% |      4.07 | `TotalAreaVTBL4`
|   134.8% |                4.84 |      206,665,264.34 |    1.4% |           13.25 |           20.96 |  0.632 |           4.00 |   19.1% |      3.07 | `TotalAreaSwitch`
|   135.8% |                4.81 |      208,085,154.16 |    0.1% |           11.19 |           21.01 |  0.533 |           3.44 |   22.3% |      3.03 | `TotalAreaSwitch4`
|   319.9% |                2.04 |      490,265,491.04 |    0.7% |            8.00 |            8.90 |  0.899 |           1.00 |    0.0% |      1.29 | `TotalAreaUnion`
|   317.4% |                2.06 |      486,494,378.92 |    2.8% |            4.75 |            8.79 |  0.540 |           0.25 |    0.0% |      1.29 | `TotalAreaUnion4`
|   113.2% |                5.76 |      173,543,902.55 |    0.5% |           13.25 |           25.12 |  0.527 |           4.00 |   19.1% |      3.64 | `TotalAreaSwitchPtr`
|   114.8% |                5.68 |      175,989,847.19 |    0.6% |           11.03 |           24.72 |  0.446 |           3.25 |   23.7% |      3.59 | `TotalAreaSwitchPtr4`
|    97.1% |                6.72 |      148,777,980.28 |    0.2% |           13.50 |           29.35 |  0.460 |           3.00 |   25.0% |      4.26 | `RawVector`
|   100.0% |                6.53 |      153,224,698.33 |    0.2% |           13.50 |           28.51 |  0.473 |           3.00 |   25.0% |      4.09 | `UniqueVector`
|    99.9% |                6.53 |      153,035,983.98 |    0.1% |           13.50 |           28.53 |  0.473 |           3.00 |   25.0% |      4.09 | `Shape Collection`
|    97.7% |                6.68 |      149,680,234.13 |    0.1% |           13.50 |           29.20 |  0.462 |           3.00 |   25.0% |      4.18 | `Accumulate`
|   314.3% |                2.08 |      481,738,039.03 |    1.1% |            0.82 |            8.53 |  0.096 |           0.21 |   23.9% |      1.31 | `Shape Collection Parallel`
|   510.2% |                1.28 |      781,890,208.73 |    1.3% |            1.09 |            5.15 |  0.212 |           0.21 |   23.9% |      0.81 | `Shape Collection TBB`
|    97.1% |                6.72 |      148,770,069.36 |    0.2% |           25.50 |           29.39 |  0.868 |           5.00 |   15.0% |      4.25 | `Variant Collection`
|   411.2% |                1.59 |      630,267,149.53 |    0.6% |            9.25 |            6.92 |  1.337 |           2.00 |    0.0% |      0.99 | `MultiCollection`
|   415.4% |                1.57 |      636,729,558.42 |    0.8% |            9.25 |            6.84 |  1.353 |           2.00 |    0.0% |      0.99 | `MultiCollectionTemplate`
|   414.7% |                1.57 |      635,653,441.12 |    0.1% |            9.25 |            6.86 |  1.349 |           2.00 |    0.0% |      0.99 | `MultiCollectionTemplateParallel`
| 2,034.7% |                0.32 |    3,118,443,735.50 |    2.6% |            1.24 |            1.33 |  0.932 |           0.18 |    0.6% |      0.21 | `MultiCollection TBB`
| 2,229.6% |                0.29 |    3,417,104,161.17 |    5.3% |            1.09 |            1.21 |  0.896 |           0.15 |    0.5% |      0.18 | `MultiCollection TBB 2`
|    58.9% |               11.08 |       90,221,532.38 |    0.5% |           13.50 |           48.21 |  0.280 |           3.00 |    0.0% |      6.97 | `SortedCollection`
|362,606,976.0% |                0.00 |555,745,280,000,000.00 |    3.8% |            0.00 |            0.00 |  1.115 |           0.00 |    0.4% |      0.01 | `Cached Collection`


Elephants in the room
=====================

1. Most code in all programs, and all code in most programs is never bottle-necked on CPU performance, it is waiting for the network, or the disk, or the user.
Clean code is mostly about improving developer performance for that code, leaving time to do extra optimisation for the tiny minority of code where CPU efficiency matters.
You can compare the cost for 1 hour of a developer vs. 1 hour of AWS instance time to see the relative cost of / demand for creating software vs. running software.

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

MIT licenced.
