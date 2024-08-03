#include "PolyCollectionRunner.h"

#include "../random.h"


PolyCollectionType createPolyShapeContainer(int seed, u32 shapeCount)
{
    PolyCollectionType c;
    Randomizer r{seed};
    
    for (auto i=0; i<shapeCount; i++)
    {
        const auto t = r.randomShapeType();
        const auto p1 = r.randomParam();
        
        switch(t)
        {
            case SQUARE:
                c.insert(square(p1));
                break;
            case RECTANGLE:
                c.insert(rectangle(p1, r.randomParam()));
                break;
            case TRIANGLE:
                c.insert(triangle(p1, r.randomParam()));
                break;
            case CIRCLE:
                c.insert(circle(p1));
                break;
            default:
                throw std::invalid_argument("Bad random shape");
        }
    }
    return c;
}

param_type PolyCollectionTotalArea(const PolyCollectionType& c)
{
    param_type result;
    for (const auto& s : c)
    {
        result += s.Area();
    }
    return result;
}
