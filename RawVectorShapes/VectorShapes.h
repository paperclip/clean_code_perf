#pragma once

#include "../listing22.h"

#include <vector>

using ShapeVector = std::vector<shape_base*>;

f32 TotalAreaRawVector(const ShapeVector& shapes);

namespace RawVectorShapes
{
    ShapeVector create(int seed, u32 shapeCount);
    void destroy(ShapeVector& shapes);
}
