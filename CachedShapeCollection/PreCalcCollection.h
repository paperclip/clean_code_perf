#pragma once

#include "../ShapeCollection/SimpleShapeCollectionBase.h"

class PreCalcCollection : public SimpleShapeCollectionBase
{
public:
    /**
     * Get a short-description of the test
     */
    std::string description() override
    {
        return "PreCalcCollection";
    }
    
    void postSetup() override;

    // Test method
    param_type TotalArea() override
    {
        return m_totalArea;
    }

private:
    param_type m_totalArea = 0.0;
};