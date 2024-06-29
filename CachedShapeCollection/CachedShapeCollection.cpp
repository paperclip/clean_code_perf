
#include "CachedShapeCollection.h"

#include "../raw_virtual.h"

#include <cassert>

CachedShapeCollection::CachedShapeCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_shapes.reserve(shapeCount);
    bool print = false;
    for (auto i=0; i<shapeCount; i++)
    {
        std::unique_ptr<shape_base> shape{RawVirtual::createShape(r, print)};
        assert(shape);
        m_shapes.push_back(std::move(shape));
        if (i > 10)
        {
            print = false;
        }
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
