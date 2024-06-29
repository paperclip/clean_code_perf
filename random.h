
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
};
