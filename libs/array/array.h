#ifndef _array_h
#define _array_h

#include <cstddef>

namespace dynamic_array
{

    struct GrowthFactor
    {
        static constexpr float Half = 1.5f;
        static constexpr float Double = 2.0f;
    };
    

    template <typename T>
    class Array
    {
    private:
        T* m_Array;
        size_t m_Size, m_Capacity;
        GrowthFactor m_GrowthFactor;

        void ReSize(size_t newCapacity);

    public:
        Array(size_t capacity = 2, GrowthFactor growthFactor = GrowthFactor::Half);
        ~Array();

        T& push(const T& data);
        T& push(const T&& data);

        template<typename... Args>
        T& emplace(Args&&... args);

        void pop();
        void clear();

        const T& operator [] (size_t index) const;
        T& operator [] (size_t index);

        size_t size() const;
    };

} // namespace dynamic_array


#endif
