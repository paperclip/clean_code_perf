
#include "MultipleAccumulatorCollection.h"

#include <iostream>

param_type MultipleAccumulatorCollection::TotalArea()
{
    std::vector<double> results;
    results.push_back(0.0);
    for (const auto& shape : m_shapes)
    {
        auto area = shape->Area();
        if (results.back() > area * 10e4)
        {
            // std::cerr << "New Accumulator: " << results.back() << '\n';
            results.push_back(0.0);
        }
        results.back() += area;
    }
    double result{0.0};
    for (const auto& r : results)
    {
        result += r;
    }
    return static_cast<param_type>(result);
}
