#pragma once

#include "../ShapeCollectionBase.h"

#include <memory>
#include <vector>
#include <variant>

class VariantCollection : public ShapeCollectionBase
{
public:
    using VariantShape = std::variant<square,rectangle,triangle,circle>;
    using ShapeVector = std::vector<VariantShape>;


    /**
     * Reserve space for n items
     */
    void reserve(std::size_t n) override;

    void insertSquare(param_type side) override;
    void insertRectangle(param_type width, param_type height) override;
    void insertCircle(param_type radius) override;
    void insertTriangle(param_type base, param_type height) override;

protected:
    ShapeVector m_shapes;
};

class VariantCollectionLambda : public VariantCollection
{
    public:
        param_type TotalArea() override;

        std::string description()
        {
            return "Variant Lambda";
        }
};


class VariantCollectionStruct : public VariantCollection
{
    public:
        param_type TotalArea() override;

        std::string description()
        {
            return "Variant Struct";
        }
};


