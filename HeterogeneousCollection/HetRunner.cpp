
#include "HetRunner.h"

#include "../random.h"


andyg::heterogeneous_container createHeterogeneousShapeContainer(int seed, u32 shapeCount)
{
    andyg::heterogeneous_container c;
    Randomizer r{seed};
    
    for (auto i=0; i<shapeCount; i++)
    {
        const auto t = r.randomShapeType();
        const auto p1 = r.randomParam();
        
        switch(t)
        {
            case SQUARE:
                c.push_back(square(p1));
                break;
            case RECTANGLE:
                c.push_back(rectangle(p1, r.randomParam()));
                break;
            case TRIANGLE:
                c.push_back(triangle(p1, r.randomParam()));
                break;
            case CIRCLE:
                c.push_back(circle(p1));
                break;
            default:
                throw std::invalid_argument("Bad random shape");
        }
    }
    return c;
}

namespace
{
    struct Summer : andyg::visitor_base<square, rectangle, triangle, circle>
    {
        param_type total_{0};

        template<class T>
        void operator()(T& _in) 
        {
            total_ += _in.Area();
        }
    };
}

param_type HeterogeneousTotalArea(andyg::heterogeneous_container& c)
{
    Summer s;
    c.visit(s);
    return s.total_;
}
