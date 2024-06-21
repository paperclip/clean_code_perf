
#include "ShapeCollection.h"

#include "../raw_virtual.h"

ShapeCollection::ShapeCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_shapes.reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        std::unique_ptr<shape_base> shape{RawVirtual::createShape(r)};
        m_shapes.push_back(std::move(shape));
    }
}

param_type ShapeCollection::TotalArea()
{
    param_type result = 0.0;
    for (const auto& shape : m_shapes)
    {
        result += shape->Area();
    }
    return result;    
}
