
#pragma once

#include "listing22.h"

namespace RawVirtual
{
    shape_base** createShapes(int seed, u32 countShapes);
    void deleteShapes(shape_base** shapes, u32 countShapes);
}
