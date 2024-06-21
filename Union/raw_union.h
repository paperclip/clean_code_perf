
#pragma once
#include "shape_union.h"

namespace RawUnion
{
    shape_union* createShapes(int seed, u32 countShapes);
    shape_union** createShapePtrs(int seed, u32 countShapes);
    void deleteShapes(shape_union* shapes);
    void deleteShapes(shape_union** shapes, u32 countShapes);
}
