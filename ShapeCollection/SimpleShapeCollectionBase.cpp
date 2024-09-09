#include "SimpleShapeCollectionBase.h"

/**
 * Reserve space for n items
 */
void SimpleShapeCollectionBase::reserve(std::size_t n)
{
    m_shapes.reserve(n);
}

/**
 * Add a new shape to the collection
 */
void SimpleShapeCollectionBase::insert(std::unique_ptr<shape_base>& shape)
{
    m_shapes.emplace_back(std::move(shape));
}
