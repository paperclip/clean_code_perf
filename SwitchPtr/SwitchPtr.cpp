/* ========================================================================
   LISTING 25
   ======================================================================== */

#include "SwitchPtr.h"

static f32 GetAreaSwitchPtr(shape_union* Shape)
{
    f32 Result = 0.0;
    
    switch(Shape->Type)
    {
        case Shape_Square: {Result = Shape->Width*Shape->Width;} break;
        case Shape_Rectangle: {Result = Shape->Width*Shape->Height;} break;
        case Shape_Triangle: {Result = 0.5f*Shape->Width*Shape->Height;} break;
        case Shape_Circle: {Result = Pi32*Shape->Width*Shape->Width;} break;
        
        case Shape_Count: {} break;
    }
    
    return Result;
}

f32 TotalAreaSwitchPtr(u32 ShapeCount, shape_union** Shapes)
{
    f32 Accum = 0.0f;
    
    for(u32 ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += GetAreaSwitchPtr(Shapes[ShapeIndex]);
    }

    return Accum;
}

f32 TotalAreaSwitchPtr4(u32 ShapeCount, shape_union** Shapes)
{
    f32 Accum0 = 0.0f;
    f32 Accum1 = 0.0f;
    f32 Accum2 = 0.0f;
    f32 Accum3 = 0.0f;
    
    ShapeCount /= 4;
    while(ShapeCount--)
    {
        Accum0 += GetAreaSwitchPtr(Shapes[0]);
        Accum1 += GetAreaSwitchPtr(Shapes[1]);
        Accum2 += GetAreaSwitchPtr(Shapes[2]);
        Accum3 += GetAreaSwitchPtr(Shapes[3]);
        
        Shapes += 4;
    }
    
    f32 Result = (Accum0 + Accum1 + Accum2 + Accum3);
    return Result;
}
