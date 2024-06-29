
#include "SortedCollection.h"

#include "../random.h"

#include <execution>
#include <iostream>
#include <numeric>
#include <ranges>

using namespace Sorted;

namespace
{
    shape_base* createShape(Randomizer& r)
    {
        const auto t = r.randomShapeType();
        const auto p1 = r.randomParam();
        switch(t)
        {
            case SQUARE:
                return new square(p1);
            case RECTANGLE:
                return new rectangle(p1, r.randomParam());
            case TRIANGLE:
                return new triangle(p1, r.randomParam());
            case CIRCLE:
                return new circle(p1);
            default:
                std::cerr << "Bad random shape! " << t << '\n';
                throw std::invalid_argument("Bad random shape");
        }
    }

    using shape_base_ptr = Sorted::SortedCollection::shape_base_ptr;
    bool compareShapes(const shape_base_ptr& first, const shape_base_ptr& second)
    {
        return first->operator<(*second);
    }
}

SortedCollection::SortedCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_shapes.reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        m_shapes.emplace_back(createShape(r));
    }
    std::sort(m_shapes.begin(), m_shapes.end(), compareShapes);
    // for (auto i=0; i<100; i++)
    // {
    //     std::cerr << i << " " << m_shapes[i]->str() << '\n';
    // }
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

param_type SortedCollection::TotalAreaAccumulate()
{
    auto area_fold = [](param_type acc, const shape_base_ptr& value)
    {
        return acc + value->Area();
    };
    return std::accumulate(m_shapes.cbegin(), m_shapes.cend(), 0.0, area_fold);
}

param_type SortedCollection::TotalAreaParallel()
{
    std::vector<param_type> areas;
    areas.reserve(m_shapes.size());
    auto get_area = [](const shape_base_ptr& value) -> param_type
    {
        return value->Area();
    };
    std::transform(std::execution::par_unseq, m_shapes.cbegin(), m_shapes.cend(), areas.begin(),
         get_area);

    return std::accumulate(areas.begin(), areas.end(), 0.0);
}
