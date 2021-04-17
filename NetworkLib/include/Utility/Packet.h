//---------------------------------------------------------------------------
//!	@file	Packet.cpp
//!	@brief	通信パケット
//---------------------------------------------------------------------------
#pragma once
#include "Utility/Common.h"
#include "TypeDef.h"
#include "Serializer/Serializer.h"
#include "Serializer/ByteSwap.h"

using namespace _serializer;

namespace _network::_packet {
class Packet
{
public:
    using PacketSize                    = u32;
    static const size_t MAX_PACKET_SIZE = 32 * 1024;

    void Write(std::vector<char>& buf)
    {
        buf.clear();
        Serializer se(buf);
        OnWrite(se);

        PacketSize packetSize = 0;
        {
            auto s = se.buf().size();
            if(s > MAX_PACKET_SIZE) {
                assert(!"excess MaxPacketSize");
                return;
            }
            packetSize = static_cast<PacketSize>(s);
        }

        {
            // update the header size in buf
            auto* p = reinterpret_cast<PacketSize*>(se.buf().data());
            *p      = my_hton(packetSize);
        }
    }

    void Read(const std::vector<char>& buf)
    {
        Deserializer de(buf);
        OnRead(de);
    }

    void Read(const std::string& buf)
    {
        Deserializer de(buf);
        OnRead(de);
    }

protected:
    // Serializer
    virtual void OnWrite(_serializer::Serializer& se)  = 0;
    virtual void OnRead(_serializer::Deserializer& se) = 0;

    virtual void io(Serializer& se)   = 0;
    virtual void io(Deserializer& se) = 0;

    virtual std::string ToString() = 0;
    // TODO: Json Conventer
    //virtual void OnToJson(Serializer& se) = 0;
    //virtual void OnFromJson(Deserializer& se) = 0;
};
}   // namespace _network::_packet