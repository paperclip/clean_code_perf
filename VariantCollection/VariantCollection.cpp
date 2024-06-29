
#include "VariantCollection.h"

#include "../raw_virtual.h"

#include <stdexcept>

VariantCollection::VariantCollection(int seed, u32 shapeCount)
{
    Randomizer r{seed};

    m_shapes.reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        auto t = r.randomShapeType();
        auto p1 = r.randomParam();
        switch(t)
        {
            case SQUARE:
                m_shapes.emplace_back(square{p1});
                break;
            case RECTANGLE:
                m_shapes.emplace_back(rectangle{p1, r.randomParam()});
                break;
            case TRIANGLE:
                m_shapes.emplace_back(triangle{p1, r.randomParam()});
                break;
            case CIRCLE:
                m_shapes.emplace_back(circle{p1});
                break;
            default:
                throw std::invalid_argument("Bad random shape");
        }
    }
}

param_type VariantCollection::TotalArea()
{
    param_type result = 0.0;
    for (const auto& shape : m_shapes)
    {
        std::visit([&result](auto&& arg){result += arg.Area(); }, shape);
    }
    return result;    
}

