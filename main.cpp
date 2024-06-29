
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
#include "SortedCollection/SortedCollection.h"

#include "nanobench.h"
#include "random.h"
#include "raw_virtual.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

bool closeEnough(param_type expectedResult, param_type actualResult)
{
    auto difference = std::abs(expectedResult - actualResult);
    auto relativeDiff = difference / expectedResult;
    if (relativeDiff < 1e-10)
    {
        return true;
    }
    std::cerr << "Difference too big between " << expectedResult << " and " << actualResult
         << " diff=" << difference 
         << " relativeDiff=" << relativeDiff << '\n';
    return false;
}

int main(int argc, char* argv[]) 
{
    int seed = 12345;
    if (argc >= 2) {
	    seed = strtol(argv[1], NULL, 10);
    }

    // Count has to be a multiple of 4 for the by4 algorithms to work
    constexpr int countShapes = 1048576; // 1048576 * 2;
    using namespace ankerl::nanobench;
    auto bench = ankerl::nanobench::Bench();
    bench.batch(countShapes);
    bench.unit("shape");
    bench.minEpochIterations(50);

    param_type expectedResult = 0.0;
    
    {
        auto shapes = RawVirtual::createShapes(seed, countShapes);
        expectedResult = TotalAreaVTBL::TotalArea(countShapes, shapes);
        // std::cerr << "Expected result=" << expectedResult << '\n';
        auto vtbl4Result = TotalAreaVTBL4::TotalArea(countShapes, shapes);
        // std::cerr << "TotalAreaVTBL4::TotalArea(countShapes, shapes) = " << vtbl4Result << '\n';
        // std::cerr << "Diff = " << (expectedResult - vtbl4Result) << '\n';
        assert(closeEnough(expectedResult, vtbl4Result));

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
        assert(closeEnough(expectedResult, TotalAreaSwitch(countShapes, shapes)));

        bench.run("TotalAreaSwitch", [&]() {
            doNotOptimizeAway(TotalAreaSwitch(countShapes, shapes));
        });
        assert(closeEnough(expectedResult, TotalAreaSwitch4(countShapes, shapes)));
        bench.run("TotalAreaSwitch4", [&]() {
            doNotOptimizeAway(TotalAreaSwitch4(countShapes, shapes));
        });
        assert(closeEnough(expectedResult, TotalAreaUnion(countShapes, shapes)));
        bench.run("TotalAreaUnion", [&]() {
            doNotOptimizeAway(TotalAreaUnion(countShapes, shapes));
        });
        assert(closeEnough(expectedResult, TotalAreaUnion4(countShapes, shapes)));
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
        assert(closeEnough(expectedResult, shapes.TotalArea()));
        bench.run("Shape Collection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
        bench.run("Accumulate", [&]() {
            doNotOptimizeAway(shapes.TotalAreaAccumulate());
        });
        bench.run("Shape Collection Parallel", [&]() {
            doNotOptimizeAway(shapes.TotalAreaParallel());
        });
#ifdef HAVE_TBB
        assert(closeEnough(expectedResult, shapes.TotalAreaTBB_test()));
        // bench.run("Shape Collection TBB test", [&]() {
        //     doNotOptimizeAway(shapes.TotalAreaTBB_test());
        // });
        assert(closeEnough(expectedResult, shapes.TotalAreaTBB()));
        bench.run("Shape Collection TBB", [&]() {
            doNotOptimizeAway(shapes.TotalAreaTBB());
        });
#endif
    }
    {
        auto shapes = VariantCollection(seed, countShapes);
        bench.run("Variant Collection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
    }
    {
        auto shapes = MultiCollection(seed, countShapes);
        assert(closeEnough(expectedResult, shapes.TotalArea()));
        bench.run("MultiCollection", [&]() {
            doNotOptimizeAway(shapes.TotalArea());
        });
        bench.run("MultiCollectionTemplate", [&]() {
            doNotOptimizeAway(shapes.TotalAreaTemplate());
        });
        bench.run("MultiCollectionTemplateParallel", [&]() {
            doNotOptimizeAway(shapes.TotalAreaTemplateParallel());
        });
#ifdef HAVE_TBB
        assert(closeEnough(expectedResult, shapes.TotalAreaTbb()));
        bench.run("MultiCollection TBB", [&]() {
            doNotOptimizeAway(shapes.TotalAreaTbb());
        });
        assert(closeEnough(expectedResult, shapes.TotalAreaTbb2()));
        bench.run("MultiCollection TBB 2", [&]() {
            doNotOptimizeAway(shapes.TotalAreaTbb2());
        });
#endif
    }
    {
        auto shapes = Sorted::SortedCollection(seed, countShapes);
        bench.run("SortedCollection", [&]() {
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
