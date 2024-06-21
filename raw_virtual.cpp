
#include "raw_virtual.h"

#include "random.h"

#include <cassert>
#include <iostream>
#include <memory>

shape_base* RawVirtual::createShape(Randomizer& r)
{
    auto t = r.randomShapeType();
    shape_base* shape = nullptr;
    switch(t)
    {
        case SQUARE:
            shape = new square(r.randomParam());
            break;
        case RECTANGLE:
            shape = new rectangle(r.randomParam(), r.randomParam());
            break;
        case TRIANGLE:
            shape = new triangle(r.randomParam(), r.randomParam());
            break;
        case CIRCLE:
            shape = new circle(r.randomParam());
            break;
        default:
            std::cerr << "Bad random shape! " << t << '\n';
            throw std::invalid_argument("Bad random shape");
    }
    return shape;
}

shape_base** RawVirtual::createShapes(int seed, u32 countShapes)
{
    std::unique_ptr<shape_base*> shapes;
    shapes.reset(new shape_base*[countShapes]);

    Randomizer r{seed};

    for (int i=0; i<countShapes; i++)
    {
        shape_base* shape = createShape(r);
        shapes.get()[i] = shape;
    }
    return shapes.release();
}

void RawVirtual::deleteShapes(shape_base** shapes, u32 countShapes)
{
    for (int i=0; i<countShapes; i++)
    {
        delete shapes[i];
    }
    delete[] shapes;
}
