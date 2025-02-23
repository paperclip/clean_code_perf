#pragma once

#include "../ShapeCollection/SimpleShapeCollectionBase.h"

#include <memory>
#include <vector>

class CachedShapeCollection : public SimpleShapeCollectionBase
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

private:
    param_type m_totalArea = 0.0;
};
