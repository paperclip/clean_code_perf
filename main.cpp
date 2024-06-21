
#include "listing23.h"
#include "listing24.h"
#include "Switch/listing25.h"
#include "Union/raw_union.h"
#include "UnionTable/listing27.h"

#include "nanobench.h"
#include "random.h"
#include "raw_virtual.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) 
{
    int seed = 12345;
    if (argc >= 2) {
	    seed = strtol(argv[1], NULL, 10);
    }

    constexpr int countShapes = 1048576;
    auto bench = ankerl::nanobench::Bench();
    bench.batch(countShapes);
    bench.unit("shape");
    bench.minEpochIterations(10);
    

    {
        shape_base** shapes = RawVirtual::createShapes(seed, countShapes);

        bench.relative(true);
        bench.run("TotalAreaVTBL", [&]() {
            ankerl::nanobench::doNotOptimizeAway(TotalAreaVTBL::TotalArea(countShapes, shapes));
        });

        bench.run("TotalAreaVTBL4", [&]() {
            ankerl::nanobench::doNotOptimizeAway(TotalAreaVTBL4::TotalArea(countShapes, shapes));
        });

        RawVirtual::deleteShapes(shapes, countShapes);
    }

    {
        shape_union* shapes = RawUnion::createShapes(seed, countShapes);
        bench.run("TotalAreaSwitch", [&]() {
            ankerl::nanobench::doNotOptimizeAway(TotalAreaSwitch(countShapes, shapes));
        });
        bench.run("TotalAreaSwitch4", [&]() {
            ankerl::nanobench::doNotOptimizeAway(TotalAreaSwitch4(countShapes, shapes));
        });
        bench.run("TotalAreaUnion", [&]() {
            ankerl::nanobench::doNotOptimizeAway(TotalAreaUnion(countShapes, shapes));
        });
        bench.run("TotalAreaUnion4", [&]() {
            ankerl::nanobench::doNotOptimizeAway(TotalAreaUnion4(countShapes, shapes));
        });
        RawUnion::deleteShapes(shapes);
    }

    return 0;
}
