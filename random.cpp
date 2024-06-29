

#include "random.h"

#include <cassert>

Randomizer::Randomizer(int seed)
    : m_random(seed),
      m_double(0.0, 10.0),
      m_type(0, shape_type::END-1)
{
}

shape_type Randomizer::randomShapeType()
{
    auto shape = m_type(m_random);
    assert(shape < shape_type::END);
    return (shape_type)(shape);
}

param_type Randomizer::randomParam()
{
    return m_double(m_random);
}
