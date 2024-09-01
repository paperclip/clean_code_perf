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
    void insertShape(heco::HeterogeneousContainer_n& container, std::unique_ptr<shape_base>& shape)
    {
        assert(shape);
        T* sp = dynamic_cast<T*>(shape.get());
        container.append(*sp);
    }

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

/**
 * Add a new shape to the collection
 */
void HecoContainer::insert(std::unique_ptr<shape_base>& shape)
{
    assert(shape);
    switch (shape->Type())
    {
        case SQUARE:
            insertShape<square>(m_shapes, shape);
            break;
        case CIRCLE:
            insertShape<circle>(m_shapes, shape);
            break;
        case RECTANGLE:
            insertShape<rectangle>(m_shapes, shape);
            break;
        case TRIANGLE:
            insertShape<triangle>(m_shapes, shape);
            break;
    }
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

