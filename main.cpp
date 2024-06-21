
#include "listing23.h"
#include "listing24.h"
#include "CachedShapeCollection/CachedShapeCollection.h"
#include "RawVectorShapes/VectorShapes.h"
#include "ShapeCollection/ShapeCollection.h"
#include "Switch/listing25.h"
#include "SwitchPtr/SwitchPtr.h"
#include "Union/raw_union.h"
#include "UnionTable/listing27.h"
#include "UniqueVector/UniqueVector.h"
#include "VariantCollection/VariantCollection.h"
#include "MultiCollection/MultiCollection.h"

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

    constexpr int countShapes = 1048576 * 2;
    using namespace ankerl::nanobench;
    auto bench = ankerl::nanobench::Bench();
    bench.batch(countShapes);
    bench.unit("shape");
    bench.minEpochIterations(5);
    

    {
        auto shapes = RawVirtual::createShapes(seed, countShapes);

        bench.relative(true);
        bench.run("TotalAreaVTBL", [&]() {
            doNotOptimizeAway(TotalAreaVTBL::TotalArea(countShapes, shapes));
        });

        bench.run("TotalAreaVTBL4", [&]() {
            doNotOptimizeAway(TotalAreaVTBL4::TotalArea(countShapes, shapes));
        });

        RawVirtual::deleteShapes(shapes, countShapes);
    }

    {
        auto shapes = RawUnion::createShapes(seed, countShapes);
        bench.run("TotalAreaSwitch", [&]() {
            doNotOptimizeAway(TotalAreaSwitch(countShapes, shapes));
        });
        bench.run("TotalAreaSwitch4", [&]() {
            doNotOptimizeAway(TotalAreaSwitch4(countShapes, shapes));
        });
        bench.run("TotalAreaUnion", [&]() {
            doNotOptimizeAway(TotalAreaUnion(countShapes, shapes));
        });
        bench.run("TotalAreaUnion4", [&]() {
            doNotOptimizeAway(TotalAreaUnion4(countShapes, shapes));
        });
        RawUnion::deleteShapes(shapes);
    }
    {
        // Is all of the saving from using values not pointers?
        auto shapes = RawUnion::createShapePtrs(seed, countShapes);
        bench.run("TotalAreaSwitchPtr", [&]() {
            doNotOptimizeAway(TotalAreaSwitchPtr(countShapes, shapes));
        });
        bench.run("TotalAreaSwitchPtr4", [&]() {
            doNotOptimizeAway(TotalAreaSwitchPtr4(countShapes, shapes));
        });

        RawUnion::deleteShapes(shapes, countShapes);
    }
    {
        auto shapes = RawVectorShapes::create(seed, countShapes);
        bench.run("RawVector", [&]() {
            doNotOptimizeAway(RawVectorShapes::TotalArea(shapes));
        });

        RawVectorShapes::destroy(shapes);
    }
    {
        auto shapes = UniqueVector::create(seed, countShapes);
        bench.run("UniqueVector", [&]() {
            doNotOptimizeAway(UniqueVector::TotalArea(shapes));
        });
    }
    {
        auto shapes = ShapeCollection(seed, countShapes);
        bench.run("Shape Collection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
        bench.run("Accumulate", [&]() {
            doNotOptimizeAway(shapes.TotalAreaAccumulate());
        });
        bench.run("Transform Parallel", [&]() {
            doNotOptimizeAway(shapes.TotalAreaParallel());
        });
    }
    {
        auto shapes = VariantCollection(seed, countShapes);
        bench.run("Variant Collection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
    }
    {
        auto shapes = MultiCollection(seed, countShapes);
        bench.run("MultiCollection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
    }
    {
        auto shapes = CachedShapeCollection(seed, countShapes);
        bench.run("Cached Collection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
    }

    return 0;
}
