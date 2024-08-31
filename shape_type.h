
#pragma once

#include <cstdint>
#include <numbers>

#if __has_include(<tbb/parallel_reduce.h>)
# define HAVE_TBB 
#endif

enum shape_type
{
    SQUARE = 0,
    RECTANGLE = 1,
    TRIANGLE = 2,
    CIRCLE = 3,
    END
};

using param_type = float;
using f32 = param_type;
using u32 = uint32_t;
constexpr param_type Pi32 = std::numbers::pi;
