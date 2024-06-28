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
#ifdef HAVE_TBB
    param_type TotalAreaTBB();
    param_type TotalAreaTBB_test();
#endif
    using shape_base_ptr = std::unique_ptr<shape_base>;
    using ShapeVector = std::vector<shape_base_ptr>;
private:
    ShapeVector m_shapes;
};
