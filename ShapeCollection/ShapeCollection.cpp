
#include "ShapeCollection.h"

#include "../raw_virtual.h"

#include <execution>
#include <numeric>
#include <ranges>

ShapeCollection::ShapeCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_shapes.reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        shape_base_ptr shape{RawVirtual::createShape(r)};
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

param_type ShapeCollection::TotalAreaAccumulate()
{
    auto area_fold = [](param_type acc, const shape_base_ptr& value)
    {
        return acc + value->Area();
    };
    return std::accumulate(m_shapes.cbegin(), m_shapes.cend(), 0.0, area_fold);
}

param_type ShapeCollection::TotalAreaParallel()
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
