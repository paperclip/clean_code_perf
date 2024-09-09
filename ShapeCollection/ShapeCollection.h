#pragma once

#include "../listing22.h"
#include "SimpleShapeCollectionBase.h"

#include <memory>
#include <vector>

class ShapeCollection : public SimpleShapeCollectionBase
{
public:
    param_type TotalArea() override;
    std::string description() override
    {
        return "Shape Collection";
    }
};

class ShapeCollectionAccumulate : public SimpleShapeCollectionBase
{
public:
    param_type TotalArea() override;
    std::string description() override
    {
        return "Accumulate";
    }
};

class ShapeCollectionParallel : public SimpleShapeCollectionBase
{
public:
    param_type TotalArea() override;
    std::string description() override
    {
        return "Shape Collection Parallel";
    }
};

#ifdef HAVE_TBB
class ShapeCollectionTBB : public SimpleShapeCollectionBase
{
public:
    param_type TotalArea() override;
    std::string description() override
    {
        return "Shape Collection TBB";
    }
};
#endif