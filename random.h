
#pragma once

#include "shape_type.h"

#define SFMT_MEXP 19937

#include "mt/SFMT.h"

class Randomizer
{
    public:
        Randomizer(int seed);
        shape_type randomShapeType();
        param_type randomParam();
    private:
        sfmt_t m_mt;
};
