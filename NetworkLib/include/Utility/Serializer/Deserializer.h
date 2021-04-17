#pragma once
#include <cassert>
#include "ByteSwap.h"

namespace _serializer {

inline int8_t my_zigzag_decode(uint8_t v)
{
    return static_cast<int8_t>(v >> 1) ^ -static_cast<int8_t>(v & 1);
}
inline int16_t my_zigzag_decode(uint16_t v)
{
    return static_cast<int16_t>(v >> 1) ^ -static_cast<int16_t>(v & 1);
}
inline int32_t my_zigzag_decode(uint32_t v)
{
    return static_cast<int32_t>(v >> 1) ^ -static_cast<int32_t>(v & 1);
}
inline int64_t my_zigzag_decode(uint64_t v)
{
    return static_cast<int64_t>(v >> 1) ^ -static_cast<int64_t>(v & 1);
}

class Deserializer
{
public:
    Deserializer(const void* p, size_t n)
    {
        _r = _start = reinterpret_cast<const char*>(p);
        _end        = _r + n;
    }

    Deserializer(const std::vector<char>& buf)
    : Deserializer(buf.data(), buf.size())
    {
    }

    Deserializer(const std::string& buf)
    : Deserializer(buf.data(), buf.size())
    {
    }

    void io(int8_t& v) { io_var(v); }
    void io(int16_t& v) { io_var(v); }
    void io(int32_t& v) { io_var(v); }
    void io(int64_t& v) { io_var(v); }
    void io(uint8_t& v) { io_var(v); }
    void io(uint16_t& v) { io_var(v); }
    void io(uint32_t& v) { io_var(v); }
    void io(uint64_t& v) { io_var(v); }

    void io(float& v) { _io_fixed_number(v); }
    void io(double& v) { _io_fixed_number(v); }

    void io_raw(void* dst, size_t n)
    {
        if(_r + n > _end) {
            assert(!"unexpected end");
            // throw error
            return;
        }
        memcpy(dst, _r, n);
        _r += n;
    }

    template<typename T>
    void io(T& v)
    {
        my_serializer_io(*this, v);
    }

    //-----------------------
    void io_fixed(int8_t& v) { _io_fixed_number(v); }
    void io_fixed(int16_t& v) { _io_fixed_number(v); }
    void io_fixed(int32_t& v) { _io_fixed_number(v); }
    void io_fixed(int64_t& v) { _io_fixed_number(v); }

    void io_fixed(uint8_t& v) { _io_fixed_number(v); }
    void io_fixed(uint16_t& v) { _io_fixed_number(v); }
    void io_fixed(uint32_t& v) { _io_fixed_number(v); }
    void io_fixed(uint64_t& v) { _io_fixed_number(v); }

    void io_var(uint8_t& v) { _io_var(v); }
    void io_var(uint16_t& v) { _io_var(v); }
    void io_var(uint32_t& v) { _io_var(v); }
    void io_var(uint64_t& v) { _io_var(v); }

    void io_var(int8_t& v)
    {
        uint8_t t;
        _io_var(t);
        v = my_zigzag_decode(t);
    }
    void io_var(int16_t& v)
    {
        uint16_t t;
        _io_var(t);
        v = my_zigzag_decode(t);
    }
    void io_var(int32_t& v)
    {
        uint32_t t;
        _io_var(t);
        v = my_zigzag_decode(t);
    }
    void io_var(int64_t& v)
    {
        uint64_t t;
        _io_var(t);
        v = my_zigzag_decode(t);
    }

private:
    template<typename T>
    void _io_fixed_number(T& v)
    {
        const auto n = sizeof(v);
        if(_r + n > _end) {
            assert(!"unexpected end");
            //throw error
            return;
        }
        v = my_ntoh(*reinterpret_cast<const T*>(_r));
        _r += n;
    }

    template<typename T>
    void _io_var(T& value)
    {
        T      v   = 0;
        size_t bit = 0;
        for(size_t i = 0;; i++) {
            if(_r >= _end) {
                assert(!"MyDeserializer::io_var - unexpected end");
                //throw error
                return;
            }

            if(bit >= sizeof(value) * 8) {
                assert(!"MyDeserializer::io_var - excess number limit");
                //throw error
                return;
            }

            auto t = *_r;
            _r++;

            v |= (t & 0x7F) << bit;
            if((t & 0x80) == 0)
                break;
            bit += 7;
        }
        value = v;
    }

    const char* _start;
    const char* _r;
    const char* _end;
};
}   // namespace _serializer