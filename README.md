A response to https://www.computerenhance.com/p/clean-code-horrible-performance

I wanted to see what the code from the blog post would do on my machine, and investigate several alternative clean version could do.

| relative |            ns/shape |             shape/s |    err% |       ins/shape |       cyc/shape |    IPC |      bra/shape |   miss% |     total | benchmark
|---------:|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|   100.0% |                6.46 |      154,795,347.74 |    0.3% |           13.50 |           28.21 |  0.479 |           3.00 |   25.0% |      4.05 | `TotalAreaVTBL`
|   101.0% |                6.40 |      156,268,612.11 |    0.1% |           11.25 |           27.96 |  0.402 |           2.25 |   33.3% |      4.01 | `TotalAreaVTBL4`
|   132.4% |                4.88 |      205,011,749.69 |    0.9% |           13.25 |           21.21 |  0.625 |           4.00 |   19.2% |      3.09 | `TotalAreaSwitch`
|   134.3% |                4.81 |      207,948,689.51 |    0.3% |           11.19 |           21.02 |  0.532 |           3.44 |   22.3% |      3.04 | `TotalAreaSwitch4`
|   318.4% |                2.03 |      492,941,413.56 |    2.4% |            8.00 |            8.83 |  0.906 |           1.00 |    0.0% |      1.30 | `TotalAreaUnion`
|   315.7% |                2.05 |      488,737,201.65 |    3.9% |            4.75 |            8.92 |  0.532 |           0.25 |    0.0% |      1.30 | `TotalAreaUnion4`
|   112.4% |                5.75 |      174,024,333.41 |    0.2% |           13.25 |           25.08 |  0.528 |           4.00 |   19.1% |      3.60 | `TotalAreaSwitchPtr`
|   116.2% |                5.56 |      179,858,068.53 |    0.2% |           11.03 |           24.27 |  0.454 |           3.25 |   23.7% |      3.50 | `TotalAreaSwitchPtr4`
|    99.7% |                6.48 |      154,273,374.30 |    0.6% |           13.50 |           28.30 |  0.477 |           3.00 |   25.0% |      4.07 | `RawVector`
|    99.9% |                6.47 |      154,584,539.22 |    0.5% |           13.50 |           28.21 |  0.479 |           3.00 |   25.0% |      4.07 | `UniqueVector`
|    99.6% |                6.48 |      154,208,757.59 |    0.8% |           13.50 |           28.17 |  0.479 |           3.00 |   25.0% |      4.08 | `Shape Collection`
|    98.1% |                6.58 |      151,888,003.01 |    0.0% |           13.50 |           28.78 |  0.469 |           3.00 |   25.0% |      4.12 | `Accumulate`
|   297.5% |                2.17 |      460,480,919.63 |    2.7% |            0.85 |            8.55 |  0.099 |           0.21 |   23.8% |      1.36 | `Shape Collection Parallel`
|   454.2% |                1.42 |      703,122,000.40 |    6.1% |            1.21 |            5.58 |  0.217 |           0.23 |   23.4% |      0.87 | `Shape Collection TBB`
|    95.5% |                6.77 |      147,810,920.51 |    0.1% |           25.50 |           29.60 |  0.862 |           5.00 |   15.0% |      4.26 | `Variant Collection`
|   406.4% |                1.59 |      629,063,570.11 |    1.2% |            9.25 |            6.94 |  1.332 |           2.00 |    0.0% |      0.99 | `MultiCollection`
|   409.5% |                1.58 |      633,920,415.35 |    0.4% |            9.25 |            6.88 |  1.344 |           2.00 |    0.0% |      0.99 | `MultiCollectionTemplate`
|   406.8% |                1.59 |      629,773,666.98 |    0.4% |            9.25 |            6.93 |  1.335 |           2.00 |    0.0% |      1.00 | `MultiCollectionTemplateParallel`
| 2,086.5% |                0.31 |    3,229,790,069.11 |    2.0% |            1.17 |            1.29 |  0.910 |           0.17 |    0.6% |      0.20 | `MultiCollection TBB`
| 2,510.1% |                0.26 |    3,885,556,153.80 |    4.2% |            1.00 |            1.09 |  0.917 |           0.14 |    0.5% |      0.17 | `MultiCollection TBB 2`
|    59.4% |               10.88 |       91,935,947.12 |    0.2% |           13.50 |           47.48 |  0.284 |           3.00 |    0.0% |      6.80 | `SortedCollection`
|327,407,600.3% |                0.00 |506,811,733,333,333.38 |    4.1% |            0.00 |            0.00 |  1.084 |           0.00 |    0.4% |      0.01 | `Cached Collection`


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
* * Probably would be faster than default if we had memory fragmentation

One approach beat any of the unclean approaches:

* MultiCollection - storing each shape type in its own vector, that was 4x faster than the original, and faster than the TotalAreaUnion consistently.

The parallel and TBB approaches are much faster - but do use multiple cores to achieve this.

Testing
=======

Tests were run on x86_64 under WSL.

3rd parties
===========

* nanobench - https://github.com/martinus/nanobench/releases/tag/v4.3.11
* OneTBB - installed with "sudo apt install libtbb-dev"
* * Change Makefile to remove dependency

MIT licenced.
