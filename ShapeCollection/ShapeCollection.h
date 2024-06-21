#pragma once

#include "../listing22.h"

#include <memory>
#include <vector>

class ShapeCollection
{
public:
    ShapeCollection(int seed, u32 shapeCount);
    param_type TotalArea();
    param_type TotalAreaAccumulate();
    param_type TotalAreaParallel();
private:
    using share_base_ptr = std::unique_ptr<shape_base>;
    using ShapeVector = std::vector<share_base_ptr>;
    ShapeVector m_shapes;
};
