#include "UniqueVector.h"

#include "../raw_virtual.h"

#include <cassert>

f32 UniqueVector::TotalArea(const ShapeVector& shapes)
{
    param_type result = 0.0;
    for (const auto& shape : shapes)
    {
        result += shape->Area();
    }
    return result;
}

UniqueVector::ShapeVector UniqueVector::create(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    ShapeVector result;
    result.reserve(shapeCount);
    bool print = false;
    for (auto i=0; i<shapeCount; i++)
    {
        std::unique_ptr<shape_base> shape{RawVirtual::createShape(r, print)};
        assert(shape);
        result.push_back(std::move(shape));
        if (i > 10)
        {
            print = false;
        }
    }
    return result;
}
