#include "IncrementalCalcCollection.h"

void IncrementalCalcCollection::insert(std::unique_ptr<shape_base>& shape)
{
    m_totalArea += shape->Area();
}
