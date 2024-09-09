#pragma once

#include "shape_classes.h"

#include "../ShapeCollectionBase.h"

#include <memory>
#include <vector>

namespace Sorted
{
    class SortedCollection : public ShapeCollectionBase
    {
    public:
        param_type TotalArea() override;
        std::string description() override
        {
            return "SortedCollection";
        }
        /**
         * Post setup fix up point.
         */
        void postSetup() override;

        void insertSquare(param_type side) override;
        void insertRectangle(param_type width, param_type height) override;
        void insertCircle(param_type radius) override;
        void insertTriangle(param_type base, param_type height) override;

        /**
         * Reserve space for n items
         */
        void reserve(std::size_t n) override
        {
            m_shapes.reserve(n);
        }

        /**
         * Add a new shape to the collection
         */
        void insert(std::unique_ptr<::shape_base>& shape) override
        {
            throw std::invalid_argument("Can't insert normal shape");
        }

        using shape_base_ptr = std::unique_ptr<shape_base>;
    private:
        using ShapeVector = std::vector<shape_base_ptr>;
        ShapeVector m_shapes;
    };
}
