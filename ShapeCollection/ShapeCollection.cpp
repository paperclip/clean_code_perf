
#include "ShapeCollection.h"

#include "../raw_virtual.h"

#include <cassert>
#include <execution>
#include <numeric>
#include <ranges>

#ifdef HAVE_TBB
# include <tbb/parallel_reduce.h>
#endif

param_type ShapeCollection::TotalArea()
{
    param_type result = 0.0;
    for (const auto& shape : m_shapes)
    {
        result += shape->Area();
    }
    return result;    
}

param_type ShapeCollectionAccumulate::TotalArea()
{
    auto area_fold = [](param_type acc, const shape_base_ptr& value)
    {
        return acc + value->Area();
    };
    return std::accumulate(m_shapes.cbegin(), m_shapes.cend(), 0.0, area_fold);
}

param_type ShapeCollectionParallel::TotalArea()
{
    std::vector<param_type> areas(m_shapes.size());
    auto get_area = [](const shape_base_ptr& value) -> param_type
    {
        return value->Area();
    };
    std::transform(std::execution::par_unseq, m_shapes.cbegin(), m_shapes.cend(), areas.begin(),
         get_area);

    assert(areas.size() == m_shapes.size());

    auto total = std::accumulate(areas.begin(), areas.end(), 0.0);
    assert(total != 0);
    return total;
}

#ifdef HAVE_TBB
namespace
{
    class SumShapes
    {
        public:
            using shape_base_ptr = ShapeCollection::shape_base_ptr;
            using ShapeVector = ShapeCollection::ShapeVector;

            SumShapes( SumShapes& x, tbb::split ) 
                : m_shapes(x.m_shapes), m_result(0)
            {}

            SumShapes(const ShapeVector& shapes)
                : m_shapes(shapes), m_result(0)
            {}
            
            const ShapeVector& m_shapes;
            param_type m_result;

            void operator() (const tbb::blocked_range<size_t>& r)
            {
                param_type result = m_result;
                const auto end = r.end();
                for(size_t i=r.begin(); i!=end; ++i)
                {
                    result += m_shapes[i]->Area();
                }
                m_result = result;
            }

            void join( const SumShapes& y )
            {
                m_result += y.m_result;
            }

    };
}

param_type ShapeCollectionTBB::TotalArea()
{
    SumShapes summer{m_shapes};
    tbb::parallel_reduce(tbb::blocked_range<size_t>(0,m_shapes.size()), summer);
    return summer.m_result;
}

#endif /* HAVE_TBB */
