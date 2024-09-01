A response to https://www.computerenhance.com/p/clean-code-horrible-performance

I wanted to see what the code from the blog post would do on my machine, and investigate several alternative clean version could do.

WSL Linux x86_64:

| relative |            ns/shape |             shape/s |    err% |       ins/shape |       cyc/shape |    IPC |      bra/shape |   miss% |     total | benchmark
|---------:|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|   100.0% |                6.40 |      156,237,306.92 |    0.1% |           13.50 |           27.97 |  0.483 |           3.00 |   25.0% |      4.04 | `TotalAreaVTBL`
|   101.0% |                6.34 |      157,759,477.06 |    0.0% |           11.25 |           27.72 |  0.406 |           2.25 |   33.3% |      3.97 | `TotalAreaVTBL4`
|   433.7% |                1.48 |      677,623,713.47 |    0.4% |            9.25 |            6.44 |  1.436 |           2.00 |    0.0% |      0.93 | `Heterogeneous`
|   135.6% |                4.72 |      211,913,073.98 |    0.4% |           13.25 |           20.62 |  0.643 |           4.00 |   19.1% |      2.96 | `TotalAreaSwitch`
|   134.8% |                4.75 |      210,668,054.52 |    0.3% |           11.19 |           20.72 |  0.540 |           3.44 |   22.3% |      2.99 | `TotalAreaSwitch4`
|   395.1% |                1.62 |      617,218,691.12 |    0.5% |            8.00 |            7.06 |  1.133 |           1.00 |    0.0% |      1.02 | `TotalAreaUnion`
|   393.0% |                1.63 |      613,987,789.16 |    0.9% |            4.75 |            7.09 |  0.670 |           0.25 |    0.0% |      1.05 | `TotalAreaUnion4`
|   113.3% |                5.65 |      177,055,912.20 |    0.2% |           13.25 |           24.67 |  0.537 |           4.00 |   19.1% |      3.54 | `TotalAreaSwitchPtr`
|   116.0% |                5.52 |      181,186,144.78 |    0.4% |           11.03 |           24.10 |  0.458 |           3.25 |   23.7% |      3.49 | `TotalAreaSwitchPtr4`
|   100.2% |                6.39 |      156,524,503.17 |    0.1% |           13.50 |           27.92 |  0.483 |           3.00 |   25.0% |      4.01 | `RawVector`
|   100.2% |                6.39 |      156,583,822.66 |    0.1% |           13.50 |           27.92 |  0.484 |           3.00 |   25.0% |      4.00 | `UniqueVector`
|    95.4% |                6.71 |      148,987,537.38 |    0.1% |           25.50 |           29.37 |  0.868 |           5.00 |   15.0% |      4.20 | `Variant Lambda`
|    98.4% |                6.51 |      153,686,747.78 |    0.1% |           23.50 |           28.47 |  0.826 |           5.00 |   15.0% |      4.10 | `Variant Struct`
|    99.8% |                6.41 |      155,969,357.13 |    0.1% |           13.50 |           28.02 |  0.482 |           3.00 |   25.0% |      4.02 | `Shape Collection`
|    99.7% |                6.42 |      155,835,405.95 |    0.3% |           13.50 |           28.02 |  0.482 |           3.00 |   25.0% |      4.04 | `Accumulate`
|   282.0% |                2.27 |      440,639,643.33 |    4.6% |            0.92 |            8.85 |  0.104 |           0.23 |   23.4% |      1.47 | `Shape Collection Parallel`
|   400.2% |                1.60 |      625,264,053.47 |    2.3% |            1.17 |            5.79 |  0.202 |           0.23 |   23.3% |      1.01 | `Shape Collection TBB`
|   394.8% |                1.62 |      616,750,401.39 |    0.9% |            9.25 |            7.06 |  1.310 |           2.00 |    0.0% |      1.02 | `MultiCollection`
|   398.8% |                1.60 |      623,125,787.40 |    1.0% |            9.25 |            7.00 |  1.321 |           2.00 |    0.0% |      1.02 | `MultiCollectionTemplate`
|   386.8% |                1.65 |      604,338,319.87 |    3.3% |            9.25 |            7.22 |  1.281 |           2.00 |    0.0% |      1.06 | `MultiCollectionTemplateParallel`
| 1,169.1% |                0.55 |    1,826,598,956.23 |    6.5% |            1.44 |            2.04 |  0.707 |           0.21 |    0.8% |      0.35 | `MultiCollection TBB`
| 1,627.2% |                0.39 |    2,542,252,329.31 |   15.1% |            1.22 |            1.55 |  0.788 |           0.17 |    0.6% |      0.27 | `MultiCollection TBB 2`
|    59.8% |               10.70 |       93,475,168.87 |    1.0% |           13.50 |           46.56 |  0.290 |           3.00 |    0.0% |      6.76 | `SortedCollection`
|323,368,977.5% |                0.00 |505,222,981,818,181.75 |    9.4% |            0.00 |            0.00 |  0.836 |           0.00 |    0.4% |      0.01 | `Cached Collection`

Raspberry Pi 1

| relative |            ns/shape |             shape/s |    err% |     total | benchmark
|---------:|--------------------:|--------------------:|--------:|----------:|:----------
|   100.0% |              238.59 |        4,191,250.57 |    0.1% |    149.41 | `TotalAreaVTBL`
|   102.8% |              232.04 |        4,309,577.20 |    0.5% |    152.49 | `TotalAreaVTBL4`
|   169.9% |              140.45 |        7,119,843.70 |    0.7% |     88.07 | `Heterogeneous`
|   134.4% |              177.52 |        5,633,083.90 |    1.0% |    112.74 | `TotalAreaSwitch`
|   133.7% |              178.45 |        5,603,800.82 |    0.8% |    118.88 | `TotalAreaSwitch4`
|   146.3% |              163.05 |        6,132,902.34 |    0.2% |    102.17 | `TotalAreaUnion`
|   174.8% |              136.52 |        7,324,758.25 |    0.7% |     85.50 | `TotalAreaUnion4`
|    93.1% |              256.15 |        3,904,017.04 |    0.3% |    166.15 | `TotalAreaSwitchPtr`
|    94.8% |              251.55 |        3,975,348.05 |    0.5% |    157.52 | `TotalAreaSwitchPtr4`
|    99.9% |              238.81 |        4,187,506.12 |    0.2% |    155.05 | `RawVector`
|    99.7% |              239.25 |        4,179,758.58 |    0.5% |    149.88 | `UniqueVector`
|    84.9% |              281.16 |        3,556,749.39 |    0.3% |    181.69 | `Variant Lambda`
|    83.7% |              284.93 |        3,509,586.13 |    0.3% |    178.20 | `Variant Struct`
|    99.6% |              239.45 |        4,176,314.52 |    0.5% |    155.25 | `Shape Collection`
|    99.9% |              238.94 |        4,185,105.04 |    0.4% |    150.06 | `Accumulate`
|    73.1% |              326.18 |        3,065,831.53 |    0.7% |    210.22 | `Shape Collection Parallel`
|    94.2% |              253.25 |        3,948,666.53 |    0.2% |    158.67 | `Shape Collection TBB`
|   171.1% |              139.41 |        7,173,240.11 |    0.2% |     87.28 | `MultiCollection`
|   169.2% |              141.05 |        7,089,741.12 |    1.0% |     93.66 | `MultiCollectionTemplate`
|   170.1% |              140.25 |        7,130,163.28 |    0.5% |     89.44 | `MultiCollectionTemplateParallel`
|   139.0% |              171.60 |        5,827,591.35 |    0.4% |    107.72 | `MultiCollection TBB`
|   139.0% |              171.65 |        5,825,899.66 |    0.1% |    107.81 | `MultiCollection TBB 2`
|    72.1% |              331.03 |        3,020,904.58 |    0.7% |    212.68 | `SortedCollection`
|225,163,918.3% |           0.00 |9,437,184,000,000.00 |    7.4% |      0.26 | :wavy_dash: `Cached Collection`



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
* https://github.com/FabienPean/heco_experiments/blob/master/heco_n_map_vector.h
* boost poly-collection
* https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/

MIT licenced.
