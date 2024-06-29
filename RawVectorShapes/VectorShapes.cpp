
#include "VectorShapes.h"

#include "../raw_virtual.h"

#include <cassert>

f32 RawVectorShapes::TotalArea(const RawVectorShapes::ShapeVector& shapes)
{
    param_type result = 0.0;
    for (const auto* shape : shapes)
    {
        result += shape->Area();
    }
    return result;
}

namespace RawVectorShapes
{
    ShapeVector create(int seed, u32 shapeCount)
    {
        Randomizer r{seed};

        ShapeVector result;
        result.reserve(shapeCount);
        for (auto i=0; i<shapeCount; i++)
        {
            auto* shape = RawVirtual::createShape(r);
            assert(shape != nullptr);
            result.push_back(shape);
        }
        return result;
    }
    void destroy(ShapeVector& shapes)
    {
        for (auto* shape : shapes)
        {
            delete shape;
        }
    }
}
