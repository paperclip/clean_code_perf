#pragma once

#include "../listing22.h"

#include <memory>
#include <vector>

class ShapeCollection
{
public:
    ShapeCollection(int seed, u32 shapeCount);
    param_type TotalArea();
private:
    using ShapeVector = std::vector<std::unique_ptr<shape_base>>;
    ShapeVector m_shapes;
};
