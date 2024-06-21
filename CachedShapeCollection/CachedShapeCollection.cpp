
#include "CachedShapeCollection.h"

#include "../raw_virtual.h"

CachedShapeCollection::CachedShapeCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_shapes.reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        std::unique_ptr<shape_base> shape{RawVirtual::createShape(r)};
        m_shapes.push_back(std::move(shape));
    }
}

param_type CachedShapeCollection::TotalArea()
{
    if (m_totalArea == 0.0)
    {
        for (const auto& shape : m_shapes)
        {
            m_totalArea += shape->Area();
        }
    }
    return m_totalArea;    
}
