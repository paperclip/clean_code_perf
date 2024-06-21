#include "MultiCollection.h"

#include "../random.h"

#include <stdexcept>

MultiCollection::MultiCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_squares.reserve(shapeCount);
    m_rectangles.reserve(shapeCount);
    m_triangles.reserve(shapeCount);
    m_circles.reserve(shapeCount);

    for (auto i=0; i<shapeCount; i++)
    {
        auto t = r.randomShapeType();
        switch(t)
        {
            case SQUARE:
                m_squares.emplace_back(r.randomParam());
                break;
            case RECTANGLE:
                m_rectangles.emplace_back(r.randomParam(), r.randomParam());
                break;
            case TRIANGLE:
                m_triangles.emplace_back(r.randomParam(), r.randomParam());
                break;
            case CIRCLE:
                m_circles.emplace_back(r.randomParam());
                break;
            default:
                throw std::invalid_argument("Bad random shape");
        }
    }}
param_type MultiCollection::TotalArea()
{
    param_type result = 0.0;
    for (const auto& shape : m_squares)
    {
        result += shape.Area();
    }
    for (const auto& shape : m_rectangles)
    {
        result += shape.Area();
    }
    for (const auto& shape : m_triangles)
    {
        result += shape.Area();
    }
    for (const auto& shape : m_circles)
    {
        result += shape.Area();
    }
    return result;
}