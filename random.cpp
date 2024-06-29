

#include "random.h"

#include <cassert>

Randomizer::Randomizer(int seed)
    : m_random(seed)
{
}

shape_type Randomizer::randomShapeType()
{
    static std::uniform_int_distribution<uint64_t> typeGenerator{0, shape_type::END-1};
    const auto shape = typeGenerator(m_random);
    assert(shape < shape_type::END);
    return static_cast<shape_type>(shape);
}

param_type Randomizer::randomParam()
{
    static std::uniform_real_distribution<param_type> doubleGenerator{0, 10};
    return doubleGenerator(m_random);
}
