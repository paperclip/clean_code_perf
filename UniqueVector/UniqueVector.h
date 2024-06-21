#pragma once
#include "../listing22.h"

#include <memory>
#include <vector>




namespace UniqueVector
{
    using ShapeVector = std::vector<std::unique_ptr<shape_base>>;
    
    f32 TotalArea(const ShapeVector& shapes);
    ShapeVector create(int seed, u32 shapeCount);
    // No need for destroy...
}
