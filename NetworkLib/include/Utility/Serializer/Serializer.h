#pragma once
#include "../Common.h"
#include <cassert>
#include "Deserializer.h"

namespace _serializer {
inline uint8_t my_zigzag_encode(int8_t v)
{
    const auto a = static_cast<uint8_t>(v) << 1;   // shift in unsigned
    const auto b = static_cast<uint8_t>(v >> 7);   // ! must shift in signed
    return a ^ b;
}

inline uint16_t my_zigzag_encode(int16_t v)
{
    const auto a = static_cast<uint16_t>(v) << 1;    // shift in unsigned
    const auto b = static_cast<uint16_t>(v >> 15);   // ! must shift in signed
    return a ^ b;
}

inline uint32_t my_zigzag_encode(int32_t v)
{
    const auto a = static_cast<uint32_t>(v) << 1;    // shift in unsigned
    const auto b = static_cast<uint32_t>(v >> 31);   // ! must shift in signed
    return a ^ b;
}

inline uint64_t my_zigzag_encode(int64_t v)
{
    const auto a = static_cast<uint64_t>(v) << 1;    // shift in unsigned
    const auto b = static_cast<uint64_t>(v >> 63);   // ! must shift in signed
    return a ^ b;
}

template<typename SE, typename T>
void my_serializer_io(SE& se, T& v);

class Serializer
{
public:
    Serializer(std::vector<char>& buf)
    : _buf(buf)
    {
    }

    void io(s8 v) { io_var(v); }
    void io(s16 v) { io_var(v); }
    void io(s32 v) { io_var(v); }
    void io(s64 v) { io_var(v); }

    void io(u8 v) { io_var(v); }
    void io(u16 v) { io_var(v); }
    void io(u32 v) { io_var(v); }
    void io(u64 v) { io_var(v); }

    void io(f32 v) { _io_fixed_number(v); }
    void io(f64 v) { _io_fixed_number(v); }

    template<typename T>
    void io(T& v)
    {
        my_serializer_io(*this, v);
    }

    void io_raw(const void* p, size_t n)
    {
        const auto s = _buf.size();
        _buf.resize(s + n);
        memcpy(&_buf[s], p, n);
    }

    //-----------------------
    void io_fixed(int8_t v) { _io_fixed_number(v); }
    void io_fixed(int16_t v) { _io_fixed_number(v); }
    void io_fixed(int32_t v) { _io_fixed_number(v); }
    void io_fixed(int64_t v) { _io_fixed_number(v); }

    void io_fixed(uint8_t v) { _io_fixed_number(v); }
    void io_fixed(uint16_t v) { _io_fixed_number(v); }
    void io_fixed(uint32_t v) { _io_fixed_number(v); }
    void io_fixed(uint64_t v) { _io_fixed_number(v); }

    void io_var(uint8_t v)
    {
        if(v >> 7) return _io_var<uint8_t, 2>(v);
        return _io_var<uint8_t, 1>(v);
    }
    void io_var(uint16_t v)
    {
        if(v >> 14) return _io_var<uint16_t, 3>(v);
        if(v >> 7) return _io_var<uint16_t, 2>(v);
        return _io_var<uint16_t, 1>(v);
    }
    void io_var(uint32_t v)
    {
        if(v >> 28) return _io_var<uint32_t, 5>(v);
        if(v >> 21) return _io_var<uint32_t, 4>(v);
        if(v >> 14) return _io_var<uint32_t, 3>(v);
        if(v >> 7) return _io_var<uint32_t, 2>(v);
        return _io_var<uint32_t, 1>(v);
    }
    void io_var(uint64_t v)
    {
        if(v >> 63) return _io_var<uint64_t, 10>(v);
        if(v >> 56) return _io_var<uint64_t, 9>(v);
        if(v >> 49) return _io_var<uint64_t, 8>(v);
        if(v >> 42) return _io_var<uint64_t, 7>(v);
        if(v >> 35) return _io_var<uint64_t, 6>(v);
        if(v >> 28) return _io_var<uint64_t, 5>(v);
        if(v >> 21) return _io_var<uint64_t, 4>(v);
        if(v >> 14) return _io_var<uint64_t, 3>(v);
        if(v >> 7) return _io_var<uint64_t, 2>(v);
        return _io_var<uint64_t, 1>(v);
    }

    void io_var(int8_t v) { io_var(my_zigzag_encode(v)); }
    void io_var(int16_t v) { io_var(my_zigzag_encode(v)); }
    void io_var(int32_t v) { io_var(my_zigzag_encode(v)); }
    void io_var(int64_t v) { io_var(my_zigzag_encode(v)); }

    //-----------------------

    std::vector<char>& buf() { return _buf; }

private:
    template<typename T>
    void _io_fixed_number(T& v)
    {
        const auto s = _buf.size();
        const auto n = sizeof(v);
        _buf.resize(s + n);
        *reinterpret_cast<T*>(&_buf[s]) = my_hton(v);
    }

    template<typename T, size_t N>   // !! using Template size_t N, so compiler might unroll for loop
    void _io_var(T& value)
    {
        auto s = _buf.size();
        _buf.resize(s + N);
        auto* dst = &_buf[s];
        auto* end = dst + N;
        auto  v   = value;

        for(size_t i = 0; i < N; i++, dst++) {
            *dst = v & 0x7F;
            v >>= 7;
            if(!v)
                break;
            *dst |= 0x80;
        }
        assert(dst + 1 == end);
    }

    std::vector<char>& _buf;
};

//-------------------------------
template<typename SE, typename T>
inline void my_serializer_io(SE& se, T& v)
{
    v.io(se);
}

template<>
inline void my_serializer_io(Serializer& se, std::string& v)
{
    uint64_t n = v.size();
    se.io_var(n);
    se.io_raw(v.c_str(), v.size());
}

template<>
inline void my_serializer_io(Deserializer& se, std::string& v)
{
#undef max
    uint64_t n64;
    se.io_var(n64);
    if(n64 > std::numeric_limits<size_t>::max()) {
        assert(!"string is too big");
        return;
    }
    auto n = static_cast<size_t>(n64);
    v.resize(n);
    se.io_raw(&*v.begin(), n);
}

template<typename T>
inline void my_serializer_io(Serializer& se, std::vector<T>& v)
{
    uint64_t n = v.size();
    se.io_var(n);
    for(auto& e : v) {
        se.io(e);
    }
}

template<typename T>
inline void my_serializer_io(Deserializer& se, std::vector<T>& v)
{
#undef max
    uint64_t n64;
    se.io_var(n64);
    if(n64 > std::numeric_limits<size_t>::max()) {
        assert(!"array is too big");
        return;
    }
    auto n = static_cast<size_t>(n64);
    v.resize(n);
    for(auto& e : v) {
        se.io(e);
    }
};

}   // namespace _serializer