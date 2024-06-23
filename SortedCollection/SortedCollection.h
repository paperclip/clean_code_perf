#pragma once

#include "shape_classes.h"

#include <memory>
#include <vector>

namespace Sorted
{
    class SortedCollection
    {
    public:
        SortedCollection(int seed, u32 shapeCount);
        param_type TotalArea();
        param_type TotalAreaAccumulate();
        param_type TotalAreaParallel();
        using shape_base_ptr = std::unique_ptr<shape_base>;
    private:
        using ShapeVector = std::vector<shape_base_ptr>;
        ShapeVector m_shapes;
    };
}
