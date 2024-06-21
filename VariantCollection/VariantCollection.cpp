
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
        switch(t)
        {
            case SQUARE:
                m_shapes.emplace_back(square{r.randomParam()});
                break;
            case RECTANGLE:
                m_shapes.emplace_back(rectangle{r.randomParam(), r.randomParam()});
                break;
            case TRIANGLE:
                m_shapes.emplace_back(triangle{r.randomParam(), r.randomParam()});
                break;
            case CIRCLE:
                m_shapes.emplace_back(circle{r.randomParam()});
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

