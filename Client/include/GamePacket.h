#pragma once
#include "Utility/Packet.h"

namespace _network::_packet {

enum class PacketType : u16
{
    None,
    Start,
    Pos
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

    std::string ToString() override{
        return "";
    };

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

class GamePacket_POS : public GamePacket
{
    using Base = GamePacket;

public:
    s32 _currentPlayerId;
    f32 _x;
    f32 _y;

protected:
    virtual Type OnType() const override { return Type::Pos; }
    virtual void OnWrite(Serializer& se) override { io(se); }
    virtual void OnRead(Deserializer& se) override { io(se); }

    template<typename SE>
    void io(SE& se)
    {
        Base::io(se);
        se.io(_currentPlayerId);
        se.io(_x);
        se.io(_y);
    }

    std::string ToString() override{
        return fmt::format("POS {} {} {}\n",
                    _currentPlayerId,
                    _x,
                    _y);
    }
};
}   // namespace _network::_packet