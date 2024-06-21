/* ========================================================================
   LISTING 23
   ======================================================================== */

#include "listing23.h"

param_type TotalAreaVTBL::TotalArea(u32 ShapeCount, shape_base **Shapes)
{
    param_type Accum = 0.0;
    for(u32 ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += Shapes[ShapeIndex]->Area();
    }
    
    return Accum;
}
