
#include "VariantCollection.h"

#include "../raw_virtual.h"

#include <stdexcept>


void VariantCollection::reserve(std::size_t n)
{
    m_shapes.reserve(n);
}

void VariantCollection::insertSquare(param_type side)
{
    m_shapes.emplace_back(square{side});
}
void VariantCollection::insertRectangle(param_type width, param_type height)
{
    m_shapes.emplace_back(rectangle{width, height});
}
void VariantCollection::insertCircle(param_type radius)
{
    m_shapes.emplace_back(circle{radius});
}
void VariantCollection::insertTriangle(param_type base, param_type height)
{
    m_shapes.emplace_back(triangle{base, height});
}

param_type VariantCollectionLambda::TotalArea()
{
    param_type result = 0.0;
    for (const auto &shape : m_shapes)
    {
        std::visit([&result](auto &&arg)
                   { result += arg.Area(); }, shape);
    }
    return result;
}

namespace
{
    struct Summer
    {
        param_type total_{0};
        template <class T>
        void operator()(T &in)
        {
            total_ += in.Area();
        }
    };

    template <class V>
    void visit(V&& visitor, const VariantCollection::ShapeVector& shapes)
    {
        for (const auto& object : shapes)
        {
            std::visit(visitor, object);
        }
    }
}

param_type VariantCollectionStruct::TotalArea()
{
    Summer summer;
    visit(summer, m_shapes);
    return summer.total_;
}
