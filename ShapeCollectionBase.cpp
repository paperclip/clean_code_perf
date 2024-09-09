#include "ShapeCollectionBase.h"

#include "random.h"

#include <cassert>
#include <exception>
#include <iostream>


void ShapeCollectionBase::insertSquare(param_type side)
{
    shape_base_ptr shape = std::make_unique<square>(side);
    insert(shape);
}

void ShapeCollectionBase::insertRectangle(param_type width, param_type height)
{
    shape_base_ptr shape = std::make_unique<rectangle>(width, height);
    insert(shape);
}

void ShapeCollectionBase::insertCircle(param_type radius)
{
    shape_base_ptr shape = std::make_unique<circle>(radius);
    insert(shape);
}

void ShapeCollectionBase::insertTriangle(param_type base, param_type height)
{
    shape_base_ptr shape = std::make_unique<triangle>(base, height);
    insert(shape);
}

void ShapeCollectionBase::insertRandomShape(Randomizer& r)
{
    const auto t = r.randomShapeType();
    const auto p1 = r.randomParam();
    switch(t)
    {
        case SQUARE:
            insertSquare(p1);
            break;
        case RECTANGLE:
            insertRectangle(p1, r.randomParam());
            break;
        case TRIANGLE:
            insertTriangle(p1, r.randomParam());
            break;
        case CIRCLE:
            insertCircle(p1);
            break;
        default:
            std::cerr << "Bad random shape! " << t << '\n';
            throw std::invalid_argument("Bad random shape");
    }
}

void ShapeCollectionBase::setup(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        insertRandomShape(r);
    }
    postSetup();
}
