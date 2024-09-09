
#include "PreCalcCollection.h"

void PreCalcCollection::postSetup()
{
    for (const auto& shape : m_shapes)
    {
        m_totalArea += shape->Area();
    }
}
