#pragma once
#include "Common.h"

namespace _network {
template<typename T>
inline typename std::underlying_type<T>::type& my_enum_to_int(T& v)
{
    return *reinterpret_cast<typename std::underlying_type<T>::type*>(&v);
}

template<typename T>
inline const typename std::underlying_type<T>::type& my_enum_to_int(const T& v)
{
    return *reinterpret_cast<const typename std::underlying_type<T>::type*>(&v);
}
}