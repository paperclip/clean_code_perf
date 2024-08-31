
#include "HighAccuracyCollection.h"

void HighAccuracyCollection::reserve(std::size_t n)
{
    m_shapes.reserve(n);
}

/**
 * Add a new shape to the collection
 */
void HighAccuracyCollection::insert(std::unique_ptr<shape_base>& shape)
{
    m_shapes.emplace_back(std::move(shape));
}

namespace
{
    using shape_base_ptr = HighAccuracyCollection::shape_base_ptr;
    bool compareShapes(const shape_base_ptr& first, const shape_base_ptr& second)
    {
        return first->Area() < second->Area();
    }
}

/**
 * Post setup fix up point.
 */
void HighAccuracyCollection::postSetup()
{
    std::sort(m_shapes.begin(), m_shapes.end(), compareShapes);
}


// Test method
param_type HighAccuracyCollection::TotalArea()
{
    double result = 0.0;
    for (const auto& shape : m_shapes)
    {
        result += shape->Area();
    }
    return static_cast<param_type>(result);
}
