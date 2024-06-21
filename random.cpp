

#include "random.h"

Randomizer::Randomizer(int seed)
{
    sfmt_init_gen_rand(&m_mt, seed);
}

shape_type Randomizer::randomShapeType()
{
    auto rand = sfmt_genrand_uint64(&m_mt);
    return (shape_type)(rand % shape_type::END);
}

param_type Randomizer::randomParam()
{
    return sfmt_genrand_res53(&m_mt);
}
