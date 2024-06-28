#include "MultiCollection.h"

#include "../random.h"

#ifdef HAVE_TBB
# include <tbb/parallel_invoke.h>
# include <tbb/parallel_reduce.h>
# include <tbb/blocked_range.h>
# include <tbb/task_group.h>
#endif

#include <stdexcept>

MultiCollection::MultiCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_squares.reserve(shapeCount);
    m_rectangles.reserve(shapeCount);
    m_triangles.reserve(shapeCount);
    m_circles.reserve(shapeCount);

    for (auto i=0; i<shapeCount; i++)
    {
        auto t = r.randomShapeType();
        switch(t)
        {
            case SQUARE:
                m_squares.emplace_back(r.randomParam());
                break;
            case RECTANGLE:
                m_rectangles.emplace_back(r.randomParam(), r.randomParam());
                break;
            case TRIANGLE:
                m_triangles.emplace_back(r.randomParam(), r.randomParam());
                break;
            case CIRCLE:
                m_circles.emplace_back(r.randomParam());
                break;
            default:
                throw std::invalid_argument("Bad random shape");
        }
    }
}

namespace
{
    template<class T>
    param_type sum(const std::vector<T>& shapes)
    {
        param_type result = 0.0;
        for (const auto& shape : shapes)
        {
            result += shape.Area();
        }
        return result;
    }
}

param_type MultiCollection::TotalArea()
{
    param_type result = 0.0;
    for (const auto& shape : m_squares)
    {
        result += shape.Area();
    }
    for (const auto& shape : m_rectangles)
    {
        result += shape.Area();
    }
    for (const auto& shape : m_triangles)
    {
        result += shape.Area();
    }
    for (const auto& shape : m_circles)
    {
        result += shape.Area();
    }
    return result;
}

param_type MultiCollection::TotalAreaTemplate()
{
    param_type result = 0.0;
    result += sum(m_squares);
    result += sum(m_rectangles);
    result += sum(m_triangles);
    result += sum(m_circles);
    return result;
}


param_type MultiCollection::TotalAreaTemplateParallel()
{
    auto ret1 = sum(m_squares);
    auto ret2 = sum(m_rectangles);
    auto ret3 = sum(m_triangles);
    auto ret4 = sum(m_circles);
    return ret1 + ret2 + ret3 + ret4;
}

#ifdef HAVE_TBB


namespace
{
    template<class ShapeClass>
    class SumShapes
    {
        public:
            using ShapeVector = std::vector<ShapeClass>;

            SumShapes( SumShapes& x, tbb::split ) 
                : m_shapes(x.m_shapes), m_result(0)
            {}

            explicit SumShapes(const ShapeVector& shapes)
                : m_shapes(shapes), m_result(0)
            {}

            SumShapes(const SumShapes&) = delete;
            SumShapes(SumShapes&&) = delete;
            
            const ShapeVector& m_shapes;
            param_type m_result;

            void operator() (const tbb::blocked_range<size_t>& r)
            {
                param_type result = m_result;
                const auto end = r.end();
                for(size_t i=r.begin(); i!=end; ++i)
                {
                    result += m_shapes[i].Area();
                }
                m_result = result;
            }

            void join( const SumShapes& y )
            {
                m_result += y.m_result;
            }

            param_type operator()()
            {
                tbb::parallel_reduce(tbb::blocked_range<size_t>(0,m_shapes.size()), *this);
                return m_result;
            }
    };
}

param_type MultiCollection::TotalAreaTbb()
{
    SumShapes<square> squareSummer{m_squares};
    SumShapes<rectangle> rectangleSummer{m_rectangles};
    SumShapes<triangle> triangleSummer{m_triangles};
    SumShapes<circle> circleSummer{m_circles};
    return squareSummer() + rectangleSummer() + triangleSummer() + circleSummer();
}

param_type MultiCollection::TotalAreaTbb2()
{
    SumShapes<square> squareSummer{m_squares};
    SumShapes<rectangle> rectangleSummer{m_rectangles};
    SumShapes<triangle> triangleSummer{m_triangles};
    SumShapes<circle> circleSummer{m_circles};

    tbb::parallel_invoke(
        [&]() {
            squareSummer();
        },
        [&]() {
            rectangleSummer();
        },
        [&]() {
            triangleSummer();
        },
        [&]() {
            circleSummer();
        }
    );

    return squareSummer.m_result + rectangleSummer.m_result + triangleSummer.m_result + circleSummer.m_result;
}
#endif
