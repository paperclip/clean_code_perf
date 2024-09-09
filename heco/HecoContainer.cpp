#include "HecoContainer.h"

#include <cassert>
#include <exception>
#include <iostream>

#ifdef HAVE_TBB
# include <tbb/parallel_invoke.h>
# include <tbb/parallel_reduce.h>
# include <tbb/blocked_range.h>
# include <tbb/task_group.h>
#endif

namespace
{
    template<class T>
    param_type SumArea(heco::HeterogeneousContainer_n& container)
    {
        param_type accumulator = 0.0;
        
        if (container.contains<T>())
        {
            for (const auto& shape : container.vector<T>())
            {
                accumulator += shape.Area();
            }
        }
        return accumulator;
    }
}

HecoContainer::HecoContainer()
    : m_total(0)
{}

void HecoContainer::insertSquare(param_type side)
{
    m_shapes.append(square(side));
    m_total += 1;
}

void HecoContainer::insertRectangle(param_type width, param_type height)
{
    m_shapes.append(rectangle(width, height));
    m_total += 1;
}

void HecoContainer::insertCircle(param_type radius)
{
    m_shapes.append(circle(radius));
    m_total += 1;
}

void HecoContainer::insertTriangle(param_type base, param_type height)
{
    m_shapes.append(triangle(base, height));
    m_total += 1;
}

// Test method
param_type HecoContainer::TotalArea()
{
    param_type accumulator = 0.0;
    accumulator += SumArea<square>(m_shapes);
    accumulator += SumArea<circle>(m_shapes);
    accumulator += SumArea<rectangle>(m_shapes);
    accumulator += SumArea<triangle>(m_shapes);
    return accumulator;
}

// HecoContainerTBB

bool HecoContainerTBB::enabled()
{
#ifdef HAVE_TBB
    return true;
#else
    return false;
#endif
}

namespace
{
    template<class T>
    class Summer
    {
        public:
            explicit Summer(heco::HeterogeneousContainer_n& s)
                : m_shapes(s)
            {}

            param_type accumulator = 0.0;
            heco::HeterogeneousContainer_n& m_shapes;
            
            param_type operator()()
            {
                accumulator = SumArea<T>(m_shapes);
                return accumulator;
            }
    };
}

param_type HecoContainerTBB::TotalArea()
{
#ifdef HAVE_TBB
    Summer<square> summer1{m_shapes};
    Summer<circle> summer2{m_shapes};
    Summer<rectangle> summer3{m_shapes};
    Summer<triangle> summer4{m_shapes};

    tbb::parallel_invoke(
        [&]() {
            summer1();
        },
        [&]() {
            summer2();
        },
        [&]() {
            summer3();
        },
        [&]() {
            summer4();
        }
    );

    return summer1.accumulator + summer2.accumulator + summer3.accumulator + summer4.accumulator;
#else
    return 0.0;
#endif
}

