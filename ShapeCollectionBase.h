
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

class ISetupBase
{
public:
    using shape_base_ptr = std::unique_ptr<shape_base>;
    virtual ~ISetupBase() = default;

    /**
     * Do any pre-setup
     * Reserve space for n items
     */
    virtual void reserve(std::size_t n)
    {}

    /**
     * Post setup fix up point.
     */
    virtual void postSetup()
    {}
};

class ISetupShapeBase : virtual public ISetupBase
{
    public:

        /**
         * Add a new shape to the collection
         * Override this, or the four functions below.
         */
        virtual void insert(shape_base_ptr& shape) = 0;
};

void setupWithShapeBase(ISetupShapeBase& setup, int seed, u32 shapeCount);

class ISetupShapes : virtual public ISetupBase
{
    public:
        virtual ~ISetupShapes() = default;
        virtual void insertSquare(param_type side) = 0;
        virtual void insertRectangle(param_type width, param_type height) = 0;
        virtual void insertCircle(param_type radius) = 0;
        virtual void insertTriangle(param_type base, param_type height) = 0;
};

void setupWithShapes(ISetupShapes& setup, int seed, u32 shapeCount);

class ShapeCollectionBase : virtual public IShapeCollection, virtual public ISetupShapeBase, virtual public ISetupShapes
{
    public:
        /**
         * Add a new shape to the collection
         * Override this, or the four functions below.
         */
        void insert(shape_base_ptr& shape) override
        {
            throw std::invalid_argument("insert not implemented");
        }

        void setup(int seed, u32 shapeCount);

        void insertSquare(param_type side) override;
        void insertRectangle(param_type width, param_type height) override;
        void insertCircle(param_type radius) override;
        void insertTriangle(param_type base, param_type height) override;

};
