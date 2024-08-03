#include "PolyCollectionRunner.h"

#include "../random.h"
#include "boost/poly_collection/algorithm.hpp"

PolyCollectionType createPolyShapeContainer(int seed, u32 shapeCount)
{
    PolyCollectionType c;
    Randomizer r{seed};

    for (auto i = 0; i < shapeCount; i++)
    {
        const auto t = r.randomShapeType();
        const auto p1 = r.randomParam();

        switch (t)
        {
            case SQUARE:
                c.insert(square(p1));
                break;
            case RECTANGLE:
                c.insert(rectangle(p1, r.randomParam()));
                break;
            case TRIANGLE:
                c.insert(triangle(p1, r.randomParam()));
                break;
            case CIRCLE:
                c.insert(circle(p1));
                break;
            default:
                throw std::invalid_argument("Bad random shape");
        }
    }
    return c;
}

param_type PolyCollectionTotalAreaRangeFor(const PolyCollectionType& c)
{
    param_type result{0};
    for (const auto& s : c)
    {
        result += s.Area();
    }
    return result;
}

param_type PolyCollectionTotalAreaForEach(const PolyCollectionType& c)
{
    param_type result{0};
    boost::poly_collection::for_each(c.begin(), c.end(), [&result](const auto& x) { result += x.Area(); });
    return result;
}

param_type PolyCollectionTotalAreaForEachRestitution(const PolyCollectionType& c)
{
    param_type result{0};
    boost::poly_collection::for_each<square, rectangle, triangle, circle>(
        c.begin(), c.end(), [&result](const auto& x) { result += x.Area(); });
    return result;
}

param_type PolyCollectionTotalAreaSegmentFor(const PolyCollectionType& c)
{
    param_type result{0};
    for (const auto& seg_info : c.segment_traversal())
    {
        for (const auto& s : seg_info)
        {
            result += s.Area();
        }
    }
    return result;
}
