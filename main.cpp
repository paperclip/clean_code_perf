
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
#include "HeterogeneousCollection/HetRunner.h"
#include "PolyCollection/PolyCollectionRunner.h"
#include "HighAccuracy/HighAccuracyCollection.h"
#include "HighAccuracy/MultipleAccumulatorCollection.h"
#include "heco/HecoContainer.h"


#include "nanobench.h"
#include "random.h"
#include "raw_virtual.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

namespace
{
    void printDifference(double expectedResult, double actualResult, const std::string &note = "")
    {
        auto difference = std::abs(expectedResult - actualResult);
        auto relativeDiff = difference / expectedResult;
        std::cerr << "Difference between " << expectedResult << " and " << actualResult
                << " " << note << " diff=" << difference
                << " relativeDiff=" << relativeDiff << '\n';
    }

    bool closeEnough(double expectedResult, double actualResult, const std::string &note = "")
    {
        auto difference = std::abs(expectedResult - actualResult);
        auto relativeDiff = difference / expectedResult;
        if (relativeDiff < 1e-3)
        {
            return true;
        }
        std::cerr << "Difference too big between " << expectedResult << " and " << actualResult
                << " " << note << " diff=" << difference
                << " relativeDiff=" << relativeDiff << '\n';
        return false;
    }

    bool closeEnough(double expectedResult, ShapeCollectionBase& actual)
    {
        return closeEnough(expectedResult, actual.TotalArea(), actual.description());
    }
}

int main(int argc, char *argv[])
{
    int seed = 12345;
    if (argc >= 2)
    {
        seed = strtol(argv[1], NULL, 10);
    }

    // Count has to be a multiple of 4 for the by4 algorithms to work
    int countShapes =
#ifdef __arm__
        4096;
#else
        1048576; // 1048576 * 2;
#endif
    if (argc >= 3)
    {
        countShapes = strtol(argv[2], nullptr, 10);
    }
    std::cerr << "Shape Count: " << countShapes << '\n';
    using namespace ankerl::nanobench;
    auto bench = ankerl::nanobench::Bench();
    bench.batch(countShapes);
    bench.unit("shape");
    bench.minEpochIterations(50);
    bench.relative(true);

    param_type expectedResult = 0.0;

    {
        auto shapes = RawVirtual::createShapes(seed, countShapes);
        expectedResult = TotalAreaVTBL::TotalArea(countShapes, shapes);
        // std::cerr << "Expected result=" << expectedResult << '\n';

        bench.run("TotalAreaVTBL", [&]()
                  { doNotOptimizeAway(TotalAreaVTBL::TotalArea(countShapes, shapes)); });

        auto vtbl4Result = TotalAreaVTBL4::TotalArea(countShapes, shapes);
        // std::cerr << "TotalAreaVTBL4::TotalArea(countShapes, shapes) = " << vtbl4Result << '\n';
        // std::cerr << "Diff = " << (expectedResult - vtbl4Result) << '\n';
        assert(closeEnough(expectedResult, vtbl4Result));
        bench.run("TotalAreaVTBL4", [&]()
                  { doNotOptimizeAway(TotalAreaVTBL4::TotalArea(countShapes, shapes)); });

        RawVirtual::deleteShapes(shapes, countShapes);
    }

    std::vector<std::unique_ptr<ShapeCollectionBase>> collections;
    collections.emplace_back(std::make_unique<HighAccuracyCollection>());
    collections.emplace_back(std::make_unique<ShapeCollection>());
    collections.emplace_back(std::make_unique<ShapeCollectionAccumulate>());
    collections.emplace_back(std::make_unique<ShapeCollectionParallel>());
#ifdef HAVE_TBB
    collections.emplace_back(std::make_unique<ShapeCollectionTBB>());
#endif
    // Doesn't appear to be any more accurate than the above
    // collections.emplace_back(std::make_unique<MultipleAccumulatorCollection>());
    collections.emplace_back(std::make_unique<HecoContainer>());
    collections.emplace_back(std::make_unique<HecoContainerTBB>());
    collections.emplace_back(std::make_unique<CachedShapeCollection>());

    for (auto& shapes : collections)
    {
        assert(shapes);
        if (!shapes->enabled())
        {
            continue;
        }
        shapes->setup(seed, countShapes);
        assert(closeEnough(expectedResult, *shapes));
        // printDifference(expectedResult, shapes.TotalArea(), shapes.description());
        bench.run(shapes->description(), [&]()
                  { doNotOptimizeAway(shapes->TotalArea()); });
        shapes.reset();
    }

    {
        auto shapes = createPolyShapeContainer(seed, countShapes);

        assert(closeEnough(expectedResult, PolyCollectionTotalAreaRangeFor(shapes), " (BoostPoly RangeFor)"));
        bench.run("BoostPoly RangeFor", [&]()
                  { doNotOptimizeAway(PolyCollectionTotalAreaRangeFor(shapes)); });

        assert(closeEnough(expectedResult, PolyCollectionTotalAreaForEach(shapes), " (BoostPoly ForEach)"));
        bench.run("BoostPoly ForEach", [&]()
                  { doNotOptimizeAway(PolyCollectionTotalAreaForEach(shapes)); });

        assert(closeEnough(expectedResult, PolyCollectionTotalAreaForEachRestitution(shapes), " (BoostPoly ForEachRestitution)"));
        bench.run("BoostPoly ForEachRestitution", [&]()
                  { doNotOptimizeAway(PolyCollectionTotalAreaForEachRestitution(shapes)); });

        assert(closeEnough(expectedResult, PolyCollectionTotalAreaSegmentFor(shapes), " (BoostPoly SegFor)"));
        bench.run("BoostPoly SegFor", [&]()
                  { doNotOptimizeAway(PolyCollectionTotalAreaSegmentFor(shapes)); });
    }
    {
        auto shapes = createHeterogeneousShapeContainer(seed, countShapes);
        assert(closeEnough(expectedResult, HeterogeneousTotalArea(shapes), " (Heterogeneous)"));
        bench.run("Heterogeneous", [&]()
                  { doNotOptimizeAway(HeterogeneousTotalArea(shapes)); });
    }

    {
        auto shapes = RawUnion::createShapes(seed, countShapes);
        assert(closeEnough(expectedResult, TotalAreaSwitch(countShapes, shapes)));

        bench.run("TotalAreaSwitch", [&]()
                  { doNotOptimizeAway(TotalAreaSwitch(countShapes, shapes)); });
        assert(closeEnough(expectedResult, TotalAreaSwitch4(countShapes, shapes)));
        bench.run("TotalAreaSwitch4", [&]()
                  { doNotOptimizeAway(TotalAreaSwitch4(countShapes, shapes)); });
        assert(closeEnough(expectedResult, TotalAreaUnion(countShapes, shapes)));
        bench.run("TotalAreaUnion", [&]()
                  { doNotOptimizeAway(TotalAreaUnion(countShapes, shapes)); });
        assert(closeEnough(expectedResult, TotalAreaUnion4(countShapes, shapes)));
        bench.run("TotalAreaUnion4", [&]()
                  { doNotOptimizeAway(TotalAreaUnion4(countShapes, shapes)); });
        RawUnion::deleteShapes(shapes);
    }
    {
        // Is all of the saving from using values not pointers?
        auto shapes = RawUnion::createShapePtrs(seed, countShapes);
        bench.run("TotalAreaSwitchPtr", [&]()
                  { doNotOptimizeAway(TotalAreaSwitchPtr(countShapes, shapes)); });
        bench.run("TotalAreaSwitchPtr4", [&]()
                  { doNotOptimizeAway(TotalAreaSwitchPtr4(countShapes, shapes)); });

        RawUnion::deleteShapes(shapes, countShapes);
    }
    {
        auto shapes = RawVectorShapes::create(seed, countShapes);
        bench.run("RawVector", [&]()
                  { doNotOptimizeAway(RawVectorShapes::TotalArea(shapes)); });

        RawVectorShapes::destroy(shapes);
    }
    {
        auto shapes = UniqueVector::create(seed, countShapes);
        bench.run("UniqueVector", [&]()
                  { doNotOptimizeAway(UniqueVector::TotalArea(shapes)); });
    }
    {
        auto shapes = VariantCollection(seed, countShapes);
        assert(closeEnough(expectedResult, shapes.TotalAreaLambda(), " (VariantLambda)"));
        bench.run("Variant Lambda", [&]()
                  { doNotOptimizeAway(shapes.TotalAreaLambda()); });
        assert(closeEnough(expectedResult, shapes.TotalAreaStruct(), " (VariantStruct)"));
        bench.run("Variant Struct", [&]()
                  { doNotOptimizeAway(shapes.TotalAreaStruct()); });
    }
    {
        auto shapes = MultiCollection(seed, countShapes);
        assert(closeEnough(expectedResult, shapes.TotalArea()));
        bench.run("MultiCollection", [&]()
                  { doNotOptimizeAway(shapes.TotalArea()); });
        bench.run("MultiCollectionTemplate", [&]()
                  { doNotOptimizeAway(shapes.TotalAreaTemplate()); });
        bench.run("MultiCollectionTemplateParallel", [&]()
                  { doNotOptimizeAway(shapes.TotalAreaTemplateParallel()); });
#ifdef HAVE_TBB
        assert(closeEnough(expectedResult, shapes.TotalAreaTbb()));
        bench.run("MultiCollection TBB", [&]()
                  { doNotOptimizeAway(shapes.TotalAreaTbb()); });
        assert(closeEnough(expectedResult, shapes.TotalAreaTbb2()));
        bench.run("MultiCollection TBB 2", [&]()
                  { doNotOptimizeAway(shapes.TotalAreaTbb2()); });
#endif
    }
    {
        auto shapes = Sorted::SortedCollection(seed, countShapes);
        bench.run("SortedCollection", [&]()
                  { doNotOptimizeAway(shapes.TotalArea()); });
    }

    return 0;
}
