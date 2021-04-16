#pragma once
#include "Utility/Packet.h"

namespace _network::_packet {

enum class PacketType : u16
{
    None,
    Start
};

/// 
/// GamePacket
/// 
class GamePacket : public Packet
{
public:
    using Type = PacketType;

    Type GetType() const { return OnType(); }

protected:
    virtual Type OnType() const = 0;

    void io(Serializer& se) override
    {
        PacketSize size = 0;
        se.io_fixed(size);

        Type t = Type();
        se.io_fixed(my_enum_to_int(t));
    }

    void io(Deserializer& se) override
    {
        PacketSize size = 0;
        se.io_fixed(size);

        Type t = Type::None;
        se.io_fixed(my_enum_to_int(t));
        if(t != Type()) {
            assert(!"Packet type mismatch");
            return;
        }
    }
};

class GamePacket_Start : public GamePacket
{
    using Base = GamePacket;
public:
    s32 _currentPlayerId;
    s32 _totalPlayer;

protected:
    virtual Type OnType() const override { return Type::Start; }
    virtual void OnWrite(Serializer& se) override { io(se); }
    virtual void OnRead(Deserializer& se) override { io(se); }

    template<typename SE>
    void io(SE& se)
    {
        Base::io(se);
        se.io(_currentPlayerId);
        se.io(_totalPlayer);
    }
};
}   // namespace _network::_packet