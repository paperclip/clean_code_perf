#pragma once

#include "../shape_type.h"

enum shape_type_union : u32
{
    Shape_Square = shape_type::SQUARE,
    Shape_Rectangle = shape_type::RECTANGLE,
    Shape_Triangle = shape_type::TRIANGLE,
    Shape_Circle = shape_type::CIRCLE,
    
    Shape_Count,
};

struct shape_union
{
    shape_type_union Type;
    f32 Width;
    f32 Height;
};
