
#pragma once
#include "shape_union.h"

namespace RawUnion
{
    shape_union* createShapes(int seed, u32 countShapes);
    void deleteShapes(shape_union* shapes);
}
