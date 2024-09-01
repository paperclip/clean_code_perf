#pragma once

#include "HighAccuracyCollection.h"

class MultipleAccumulatorCollection : public HighAccuracyCollection
{
    public:
        
        // Test method
        param_type TotalArea() override;

        
        std::string description() override
        {
            return "HighAccuracyMultipleAccumulator";
        }
};