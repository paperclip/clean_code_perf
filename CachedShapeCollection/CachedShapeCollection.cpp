
#include "CachedShapeCollection.h"

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
