
#include "HeterogeneousCollection.h"

using namespace andyg;

heterogeneous_container::heterogeneous_container(const heterogeneous_container& _other)
{
    *this = _other;
}

heterogeneous_container::~heterogeneous_container()
{
    clear();
}

heterogeneous_container& heterogeneous_container::operator=(const heterogeneous_container& _other)
{
    clear();
    clear_functions = _other.clear_functions;
    copy_functions = _other.copy_functions;
    size_functions = _other.size_functions;
    for (auto&& copy_function : copy_functions)
    {
        copy_function(_other, *this);
    }
    return *this;
}

void heterogeneous_container::clear()
{
    for (auto&& clear_func : clear_functions)
    {
        clear_func(*this);
    }
}

size_t heterogeneous_container::size() const
{
    size_t sum = 0;
    for (auto&& size_func : size_functions)
    {
        sum += size_func(*this);
    }
    // gotta be careful about this overflowing
    return sum;
}
