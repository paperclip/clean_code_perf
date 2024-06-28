#pragma once

#include "../listing22.h"

#include <memory>
#include <vector>

class MultiCollection
{
public:
    MultiCollection(int seed, u32 shapeCount);
    param_type TotalArea();
    param_type TotalAreaTemplate();
    param_type TotalAreaTemplateParallel();
    param_type TotalAreaTbb();
    param_type TotalAreaTbb2();
private:
    std::vector<square> m_squares;
    std::vector<rectangle> m_rectangles;
    std::vector<triangle> m_triangles;
    std::vector<circle> m_circles;
};
