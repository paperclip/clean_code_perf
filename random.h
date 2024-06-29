
#pragma once

#include "shape_type.h"

#include <random>

class Randomizer
{
    public:
        Randomizer(int seed);
        shape_type randomShapeType();
        param_type randomParam();
    private:
        std::mt19937 m_random;
        std::uniform_real_distribution<param_type> m_double;
        std::uniform_int_distribution<uint64_t> m_type;
};
