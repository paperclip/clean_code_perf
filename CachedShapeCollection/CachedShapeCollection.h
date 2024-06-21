#pragma once

#include "../listing22.h"

#include <memory>
#include <vector>

class CachedShapeCollection
{
public:
    CachedShapeCollection(int seed, u32 shapeCount);
    param_type TotalArea();
private:
    using ShapeVector = std::vector<std::unique_ptr<shape_base>>;
    ShapeVector m_shapes;
    param_type m_totalArea = 0.0;
};
