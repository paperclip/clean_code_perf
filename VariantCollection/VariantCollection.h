#pragma once

#include "../listing22.h"

#include <memory>
#include <vector>
#include <variant>

class VariantCollection
{
public:
    VariantCollection(int seed, u32 shapeCount);
    param_type TotalArea();
private:
    using VariantShape = std::variant<square,rectangle,triangle,circle>;
    using ShapeVector = std::vector<VariantShape>;
    ShapeVector m_shapes;
};
