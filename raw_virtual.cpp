
#include "raw_virtual.h"

#include "random.h"

#include <cassert>
#include <iostream>
#include <memory>

#define PRINT(x)  std::cerr << x << '\n'

shape_base* RawVirtual::createShape(Randomizer& r, bool print)
{
    auto t = r.randomShapeType();
    shape_base* shape = nullptr;
    auto p1 = r.randomParam();
    param_type p2;
    switch(t)
    {
        case SQUARE:
            if (print)
            {
                PRINT("square(" << p1 << ")");
            }
            return new square(p1);
        case RECTANGLE:
            p2 = r.randomParam();
            if (print)
            {
                PRINT("rectangle(" << p1 << ", " << p2 << ")");
            }
            return new rectangle(p1, p2);
        case TRIANGLE:
            p2 = r.randomParam();
            if (print)
            {
                PRINT("triangle(" << p1 << ", " << p2 << ")");
            }
            return new triangle(p1, p2);
        case CIRCLE:
            if (print)
            {
                PRINT("circle(" << p1 << ")");
            }
            return new circle(p1);
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
    bool print = false;

    for (int i=0; i<countShapes; i++)
    {
        shapes.get()[i] = createShape(r, print);
        if (i > 10)
        {
            print = false;
        }
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
