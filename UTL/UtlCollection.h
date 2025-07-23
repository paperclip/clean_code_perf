#pragma once

#include "../ShapeCollection/SimpleShapeCollectionBase.h"

#include <memory>
#include <string>
#include <vector>

class UtlShapeCollection : public SimpleShapeCollectionBase
{
public:
    /**
     * Get a short-description of the test
     */
    std::string description() override
    {
        return "UTL Collection";
    }

    // Test method
    param_type TotalArea() override;
};
