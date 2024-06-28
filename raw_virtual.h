
#pragma once

#include "listing22.h"

#include "random.h"

namespace RawVirtual
{
    shape_base* createShape(Randomizer& r, bool print=false);
    shape_base** createShapes(int seed, u32 countShapes);
    void deleteShapes(shape_base** shapes, u32 countShapes);
}
