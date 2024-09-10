#pragma once

#include "../ShapeCollection/SimpleShapeCollectionBase.h"

class IncrementalCalcCollection : public ShapeCollectionBase
{
public:
    /**
     * Get a short-description of the test
     */
    std::string description() override
    {
        return "Incremental Collection";
    }

    // Test method
    param_type TotalArea() override
    {
        return m_totalArea;
    }

    void insert(std::unique_ptr<shape_base>& shape) override;

private:
    param_type m_totalArea = 0.0;
};
