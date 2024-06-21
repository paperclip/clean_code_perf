
#include "listing23.h"
#include "listing24.h"
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

    shape_base** shapes = RawVirtual::createShapes(seed, countShapes);

    ankerl::nanobench::Bench().run("TotalAreaVTBL", [&]() {
        ankerl::nanobench::doNotOptimizeAway(TotalAreaVTBL::TotalArea(countShapes, shapes));
    });

    ankerl::nanobench::Bench().run("TotalAreaVTBL4", [&]() {
        ankerl::nanobench::doNotOptimizeAway(TotalAreaVTBL4::TotalArea(countShapes, shapes));
    });

    RawVirtual::deleteShapes(shapes, countShapes);

    return 0;
}
