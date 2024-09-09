#pragma once

#include "../ShapeCollectionBase.h"

#include <memory>
#include <vector>

class CachedShapeCollection : public ShapeCollectionBase
{
public:
    /**
     * Get a short-description of the test
     */
    std::string description() override
    {
        return "Cached Collection";
    }

    // Test method
    param_type TotalArea() override;

    /**
     * Add a new shape to the collection
     */
    void insert(std::unique_ptr<shape_base>& shape) override;

    void reserve(std::size_t n) override;
private:
    using ShapeVector = std::vector<std::unique_ptr<shape_base>>;
    ShapeVector m_shapes;
    param_type m_totalArea = 0.0;
};
