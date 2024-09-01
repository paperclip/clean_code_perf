#pragma once

#include "../ShapeCollectionBase.h"

class HighAccuracyCollection : public ShapeCollectionBase
{
    public:
        std::vector<shape_base_ptr> m_shapes;
    
        /**
         * Reserve space for n items
         */
        void reserve(std::size_t n) override;
        /**
         * Add a new shape to the collection
         */
        void insert(shape_base_ptr& shape) override;

        /**
         * Post setup fix up point.
         */
        void postSetup() override;

        // Test method
        param_type TotalArea() override;

        
        std::string description() override
        {
            return "HighAccuracy";
        }
};