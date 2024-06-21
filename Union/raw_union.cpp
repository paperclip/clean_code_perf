#include "raw_union.h"

#include "../random.h"

shape_union* RawUnion::createShapes(int seed, u32 countShapes)
{
    shape_union* shapes = new shape_union[countShapes];
    
    Randomizer r{seed};

    for (int i=0; i<countShapes; i++)
    {
        auto t = r.randomShapeType();
        shapes[i].Type = t;

        switch(t)
        {
            case SQUARE:
            case CIRCLE:
                shapes[i].Width = r.randomParam();
                break;
            case TRIANGLE:
                shapes[i].Width = r.randomParam();
                shapes[i].Height = r.randomParam();
                break;
        }
    }
    return shapes;
}

void RawUnion::deleteShapes(shape_union* shapes)
{
    delete[] shapes;
}
