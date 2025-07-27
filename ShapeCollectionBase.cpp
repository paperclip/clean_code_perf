#include "ShapeCollectionBase.h"

#include "random.h"

#include <cassert>
#include <exception>
#include <iostream>


void ShapeCollectionBase::insertSquare(param_type side)
{
    shape_base_ptr shape = std::make_unique<square>(side);
    insert(shape);
}

void ShapeCollectionBase::insertRectangle(param_type width, param_type height)
{
    shape_base_ptr shape = std::make_unique<rectangle>(width, height);
    insert(shape);
}

void ShapeCollectionBase::insertCircle(param_type radius)
{
    shape_base_ptr shape = std::make_unique<circle>(radius);
    insert(shape);
}

void ShapeCollectionBase::insertTriangle(param_type base, param_type height)
{
    shape_base_ptr shape = std::make_unique<triangle>(base, height);
    insert(shape);
}

void ShapeCollectionBase::setup(int seed, u32 shapeCount)
{
    setupWithShapes(*this, seed, shapeCount);
}

static void insertRandomShape(ISetupShapes& setup, Randomizer& r)
{
    const auto t = r.randomShapeType();
    const auto p1 = r.randomParam();
    switch(t)
    {
        case SQUARE:
            setup.insertSquare(p1);
            break;
        case RECTANGLE:
            setup.insertRectangle(p1, r.randomParam());
            break;
        case TRIANGLE:
            setup.insertTriangle(p1, r.randomParam());
            break;
        case CIRCLE:
            setup.insertCircle(p1);
            break;
        default:
            std::cerr << "Bad random shape! " << t << '\n';
            throw std::invalid_argument("Bad random shape");
    }
}

namespace
{
    class SetupAdapter : public virtual ISetupShapes
    {
        public:
            SetupAdapter(ISetupShapeBase& setup) : m_setup(setup)
            {}
            void insertSquare(param_type side) override
            {
                shape_base_ptr shape = std::make_unique<square>(side);
                m_setup.insert(shape);
            }
            void insertRectangle(param_type width, param_type height) override
            {
                shape_base_ptr shape = std::make_unique<rectangle>(width, height);
                m_setup.insert(shape);
            }
            void insertCircle(param_type radius) override
            {
                shape_base_ptr shape = std::make_unique<circle>(radius);
                m_setup.insert(shape);
            }
            void insertTriangle(param_type base, param_type height) override
            {
                shape_base_ptr shape = std::make_unique<triangle>(base, height);
                m_setup.insert(shape);
            }

        private:
            ISetupShapeBase& m_setup;
    };
}

void setupWithShapeBase(ISetupShapeBase& setup, int seed, u32 shapeCount)
{
    SetupAdapter adapter{setup};
    setupWithShapes(adapter, seed, shapeCount);
}

void setupWithShapes(ISetupShapes& setup, int seed, u32 shapeCount)
{
    Randomizer r{seed};

    setup.reserve(shapeCount);
    for (auto i=0; i<shapeCount; i++)
    {
        insertRandomShape(setup, r);
    }
    setup.postSetup();
    
}