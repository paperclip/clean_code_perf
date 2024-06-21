#pragma once

#include "../listing22.h"

#include <vector>

namespace RawVectorShapes
{
    using ShapeVector = std::vector<shape_base*>;

    f32 TotalArea(const ShapeVector& shapes);

    ShapeVector create(int seed, u32 shapeCount);
    void destroy(ShapeVector& shapes);
}
