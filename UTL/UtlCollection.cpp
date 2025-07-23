
#include "UtlCollection.h"

#include "UTL/parallel.hpp"

param_type UtlShapeCollection::TotalArea()
{
    using namespace utl;

    static std::vector<param_type> areas(m_shapes.size());
    areas.resize(m_shapes.size());
    utl::parallel::blocking_loop(parallel::IndexRange{0, m_shapes.size()}, [&](int i) { areas[i] = m_shapes.at(i)->Area(); });
    return utl::parallel::blocking_reduce(areas, parallel::sum<>());
}
