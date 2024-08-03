

#pragma once

#include "../listing22.h"
#include "boost/poly_collection/base_collection.hpp"

using PolyCollectionType = boost::base_collection<shape_base>;

PolyCollectionType createPolyShapeContainer(int seed, u32 shapeCount);
param_type PolyCollectionTotalArea(const PolyCollectionType& c);
