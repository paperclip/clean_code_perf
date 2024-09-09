
#pragma once

#include "listing22.h"

#include <memory>
#include <vector>

class Randomizer;

class ShapeCollectionBase
{
    public:
        using shape_base_ptr = std::unique_ptr<shape_base>;
        /**
         * Reserve space for n items
         */
        virtual void reserve(std::size_t n) = 0;
        /**
         * Add a new shape to the collection
         */
        virtual void insert(std::unique_ptr<shape_base>& shape) = 0;

        virtual void insertSquare(param_type side);
        virtual void insertRectangle(param_type width, param_type height);
        virtual void insertCircle(param_type radius);
        virtual void insertTriangle(param_type base, param_type height);

        void insertRandomShape(Randomizer& r);
        void setup(int seed, u32 shapeCount);

        /**
         * Post setup fix up point.
         */
        virtual void postSetup() {};

        
        // Test method
        virtual param_type TotalArea() = 0;

        /**
         * Get a short-description of the test
         */
        virtual std::string description() = 0;

        /** 
         * Override to disable this collection from testing
         */
        virtual bool enabled()
        {
            return true;
        }
};
