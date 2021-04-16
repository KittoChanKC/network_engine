#pragma once
#include "../Common.h"
inline uint8_t my_byte_swap(uint8_t v)
{
    return v;
}

inline uint16_t my_byte_swap(uint16_t v)
{
    union T
    {
        uint16_t value;
        uint8_t  c[2];
    };
    T src;
    src.value = v;
    T dst;
    dst.c[0] = src.c[1];
    dst.c[1] = src.c[0];
    return dst.value;
}

inline uint32_t my_byte_swap(uint32_t v)
{
    union T
    {
        uint32_t value;
        uint8_t  c[4];
    };
    T src;
    src.value = v;
    T dst;
    dst.c[0] = src.c[3];
    dst.c[1] = src.c[2];
    dst.c[2] = src.c[1];
    dst.c[3] = src.c[0];
    return dst.value;
}

inline uint64_t my_byte_swap(uint64_t v)
{
    union T
    {
        uint64_t value;
        uint8_t  c[8];
    };
    T src;
    src.value = v;
    T dst;
    dst.c[0] = src.c[7];
    dst.c[1] = src.c[6];
    dst.c[2] = src.c[5];
    dst.c[3] = src.c[4];
    dst.c[4] = src.c[3];
    dst.c[5] = src.c[2];
    dst.c[6] = src.c[1];
    dst.c[7] = src.c[0];
    return dst.value;
}

#if 1   // byte swap needed

inline uint8_t my_hton(uint8_t v)
{
    return my_byte_swap(v);
}
inline uint16_t my_hton(uint16_t v)
{
    return my_byte_swap(v);
}
inline uint32_t my_hton(uint32_t v)
{
    return my_byte_swap(v);
}
inline uint64_t my_hton(uint64_t v)
{
    return my_byte_swap(v);
}

inline int8_t my_hton(int8_t v)
{
    return (int8_t)my_byte_swap((uint8_t)v);
}
inline int16_t my_hton(int16_t v)
{
    return (int16_t)my_byte_swap((uint16_t)v);
}
inline int32_t my_hton(int32_t v)
{
    return (int32_t)my_byte_swap((uint32_t)v);
}
inline int64_t my_hton(int64_t v)
{
    return (int64_t)my_byte_swap((uint64_t)v);
}

inline uint8_t my_ntoh(uint8_t v)
{
    return my_byte_swap(v);
}
inline uint16_t my_ntoh(uint16_t v)
{
    return my_byte_swap(v);
}
inline uint32_t my_ntoh(uint32_t v)
{
    return my_byte_swap(v);
}
inline uint64_t my_ntoh(uint64_t v)
{
    return my_byte_swap(v);
}

inline int8_t my_ntoh(int8_t v)
{
    return (int8_t)my_byte_swap((uint8_t)v);
}
inline int16_t my_ntoh(int16_t v)
{
    return (int16_t)my_byte_swap((uint16_t)v);
}
inline int32_t my_ntoh(int32_t v)
{
    return (int32_t)my_byte_swap((uint32_t)v);
}
inline int64_t my_ntoh(int64_t v)
{
    return (int64_t)my_byte_swap((uint64_t)v);
}

#else   // byte swap not needed

inline uint8_t my_hton(uint8_t v)
{
    return v;
}
inline uint16_t my_hton(uint16_t v)
{
    return v;
}
inline uint32_t my_hton(uint32_t v)
{
    return v;
}
inline uint64_t my_hton(uint64_t v)
{
    return v;
}

inline int8_t my_hton(int8_t v)
{
    return v;
}
inline int16_t my_hton(int16_t v)
{
    return v;
}
inline int32_t my_hton(int32_t v)
{
    return v;
}
inline int64_t my_hton(int64_t v)
{
    return v;
}

inline uint8_t my_ntoh(uint8_t v)
{
    return v;
}
inline uint16_t my_ntoh(uint16_t v)
{
    return v;
}
inline uint32_t my_ntoh(uint32_t v)
{
    return v;
}
inline uint64_t my_ntoh(uint64_t v)
{
    return v;
}

inline int8_t my_ntoh(int8_t v)
{
    return v;
}
inline int16_t my_ntoh(int16_t v)
{
    return v;
}
inline int32_t my_ntoh(int32_t v)
{
    return v;
}
inline int64_t my_ntoh(int64_t v)
{
    return v;
}

#endif

inline float my_hton(float v)
{
    auto t = my_hton(*(uint32_t*)&v);
    return *(float*)&t;
}
inline double my_hton(double v)
{
    auto t = my_hton(*(uint64_t*)&v);
    return *(double*)&t;
}

inline float my_ntoh(float v)
{
    auto t = my_ntoh(*(uint32_t*)&v);
    return *(float*)&t;
}
inline double my_ntoh(double v)
{
    auto t = my_ntoh(*(uint64_t*)&v);
    return *(double*)&t;
}