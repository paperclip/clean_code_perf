#include "raw_union.h"

#include "../random.h"

#include <cassert>
#include <iostream>

#define PRINT(x)  std::cerr << x << '\n'

shape_union* RawUnion::createShapes(int seed, u32 countShapes)
{
    shape_union* shapes = new shape_union[countShapes];
    
    Randomizer r{seed};
    bool print = false;

    for (int i=0; i<countShapes; i++)
    {
        shape_union& shape = shapes[i];
        auto t = static_cast<shape_type_union>(r.randomShapeType());
        assert(t < Shape_Count);
        shape.Type = t;
        auto p1 = r.randomParam();
        shape.Width = p1;

        switch(t)
        {
            case SQUARE:
                if (print)
                {
                    PRINT("square(" << p1 << ")");
                }
                shape.Height = shape.Width;
                break;
            case RECTANGLE:
                if (print)
                {
                    PRINT("rectangle(" << p1 << ", ...)");
                }
                shape.Height = r.randomParam();
                break;
            case TRIANGLE:
                if (print)
                {
                    PRINT("triangle(" << p1 << ", ...)");
                }
                shape.Height = r.randomParam();
                break;
            case CIRCLE:
                if (print)
                {
                    PRINT("circle(" << p1 << ")");
                }
                shape.Height = shape.Width;
                break;
            default:
                std::cerr << "Bad random shape! " << t << '\n';
                throw std::invalid_argument("Bad random shape");
        }

        if (i > 10)
        {
            print = false;
        }
    }
    return shapes;
}

shape_union** RawUnion::createShapePtrs(int seed, u32 countShapes)
{
    shape_union** shapes = new shape_union*[countShapes];
    Randomizer r{seed};
    
    for (int i=0; i<countShapes; i++)
    {
        auto t = static_cast<shape_type_union>(r.randomShapeType());
        shape_union* shape = new shape_union();
        shape->Type = t;
        shape->Width = r.randomParam();

        switch(t)
        {
            case TRIANGLE:
            case RECTANGLE:
                shape->Height = r.randomParam();
                break;
        }
        shapes[i] = shape;
    }
    return shapes;
}

void RawUnion::deleteShapes(shape_union* shapes)
{
    delete[] shapes;
}

void RawUnion::deleteShapes(shape_union** shapes, u32 countShapes)
{
    for (int i=0; i<countShapes; i++)
    {
        delete shapes[i];
    }
    delete[] shapes;
}
