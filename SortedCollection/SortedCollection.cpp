
#include "SortedCollection.h"

#include "../random.h"

#include <execution>
#include <iostream>
#include <numeric>
#include <ranges>

using namespace Sorted;

namespace
{
    using shape_base_ptr = Sorted::SortedCollection::shape_base_ptr;
    bool compareShapes(const shape_base_ptr& first, const shape_base_ptr& second)
    {
        return first->operator<(*second);
    }
}

void SortedCollection::postSetup()
{
    std::sort(m_shapes.begin(), m_shapes.end(), compareShapes);
}

void SortedCollection::insertSquare(param_type side)
{
    m_shapes.push_back(std::make_unique<Sorted::square>(side));
}

void SortedCollection::insertRectangle(param_type width, param_type height)
{
    m_shapes.push_back(std::make_unique<Sorted::rectangle>(width, height));
}

void SortedCollection::insertCircle(param_type radius)
{
    m_shapes.push_back(std::make_unique<Sorted::circle>(radius));
}

void SortedCollection::insertTriangle(param_type base, param_type height)
{
    m_shapes.push_back(std::make_unique<Sorted::triangle>(base, height));
}

param_type SortedCollection::TotalArea()
{
    param_type result = 0.0;
    for (const auto& shape : m_shapes)
    {
        result += shape->Area();
    }
    return result;    
}
