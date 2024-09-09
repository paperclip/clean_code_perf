
#include "CachedShapeCollection.h"

/**
 * Add a new shape to the collection
 */
void CachedShapeCollection::insert(std::unique_ptr<shape_base>& shape)
{
    m_shapes.push_back(std::move(shape));
}

void CachedShapeCollection::reserve(std::size_t n)
{
    m_shapes.reserve(n);
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
