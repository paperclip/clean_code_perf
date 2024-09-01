#include "ShapeCollectionBase.h"

#include "random.h"

#include <cassert>
#include <exception>
#include <iostream>


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
}

void ShapeCollectionBase::setup(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        shape_base_ptr shape{createShape(r)};
        assert(shape);
        insert(shape);
    }
    postSetup();
}
