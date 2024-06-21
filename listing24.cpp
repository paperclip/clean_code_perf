/* ========================================================================
   LISTING 24
   ======================================================================== */

#include "listing24.h"

param_type TotalAreaVTBL4::TotalArea(u32 ShapeCount, shape_base **Shapes)
{
    param_type Accum0 = 0.0f;
    param_type Accum1 = 0.0f;
    param_type Accum2 = 0.0f;
    param_type Accum3 = 0.0f;
    
    u32 Count = ShapeCount/4;
    while(Count--)
    {
        Accum0 += Shapes[0]->Area();
        Accum1 += Shapes[1]->Area();
        Accum2 += Shapes[2]->Area();
        Accum3 += Shapes[3]->Area();
        
        Shapes += 4;
    }
    
    param_type Result = (Accum0 + Accum1 + Accum2 + Accum3);
    return Result;
}
