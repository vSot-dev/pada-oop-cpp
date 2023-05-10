#include <iostream>

#include "array.h"

namespace dynamic_array
{

    template <typename T>
    Array<T>::Array(size_t capacity, GrowthFactor growthFactor)
    : m_Array(nullptr), m_Size(0), m_Capacity(capacity), m_GrowthFactor(growthFactor)
    {
        std::cout << m_GrowthFactor;
    }

} // namespace dynamic_array

int main()
{
    
    dynamic_array::Array<int> asf;
    return 0;
}
