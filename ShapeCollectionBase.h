
#pragma once

#include "listing22.h"

#include <memory>
#include <string>
#include <vector>

class IShapeCollection
{
    public:
        virtual ~IShapeCollection() = default;
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

class Randomizer;

class ShapeCollectionBase : public IShapeCollection
{
    public:
        using shape_base_ptr = std::unique_ptr<shape_base>;
        /**
         * Reserve space for n items
         */
        virtual void reserve(std::size_t n)
        {}

        /**
         * Add a new shape to the collection
         * Override this, or the four functions below.
         */
        virtual void insert(std::unique_ptr<shape_base>& shape)
        {
            throw std::invalid_argument("insert not implemented");
        }

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
};
