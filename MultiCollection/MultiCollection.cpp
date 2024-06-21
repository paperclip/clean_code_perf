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
    }
}

namespace
{
    template<class T>
    param_type sum(const std::vector<T>& shapes)
    {
        param_type result = 0.0;
        for (const auto& shape : shapes)
        {
            result += shape.Area();
        }
        return result;
    }
}

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

param_type MultiCollection::TotalAreaTemplate()
{
    param_type result = 0.0;
    result += sum(m_squares);
    result += sum(m_rectangles);
    result += sum(m_triangles);
    result += sum(m_circles);
    return result;
}


param_type MultiCollection::TotalAreaTemplateParallel()
{
    auto ret1 = sum(m_squares);
    auto ret2 = sum(m_rectangles);
    auto ret3 = sum(m_triangles);
    auto ret4 = sum(m_circles);
    return ret1 + ret2 + ret3 + ret4;
}