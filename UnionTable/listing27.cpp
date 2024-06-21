/* ========================================================================
   LISTING 27
   ======================================================================== */

#include "../Union/shape_union.h"

f32 const CTable[Shape_Count] = {1.0f, 1.0f, 0.5f, Pi32};
f32 GetAreaUnion(shape_union Shape)
{
    f32 Result = CTable[Shape.Type]*Shape.Width*Shape.Height;
    return Result;
}

f32 TotalAreaUnion(u32 ShapeCount, shape_union *Shapes)
{
    f32 Accum = 0.0f;
    
    for(u32 ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += GetAreaUnion(Shapes[ShapeIndex]);
    }

    return Accum;
}

f32 TotalAreaUnion4(u32 ShapeCount, shape_union *Shapes)
{
    f32 Accum0 = 0.0f;
    f32 Accum1 = 0.0f;
    f32 Accum2 = 0.0f;
    f32 Accum3 = 0.0f;
    
    ShapeCount /= 4;
    while(ShapeCount--)
    {
        Accum0 += GetAreaUnion(Shapes[0]);
        Accum1 += GetAreaUnion(Shapes[1]);
        Accum2 += GetAreaUnion(Shapes[2]);
        Accum3 += GetAreaUnion(Shapes[3]);
        
        Shapes += 4;
    }
    
    f32 Result = (Accum0 + Accum1 + Accum2 + Accum3);
    return Result;
}
