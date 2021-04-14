#pragma once
#include "Utility/Packet.h"

namespace _network::_packet {

enum class PacketType : u16
{
    None,
    Start
};

class GamePacket : public Packet
{
public:
    using Type = PacketType;

    Type GetType() const { return OnType(); }

protected:
    virtual Type OnType() const = 0;
};

class GamePacket_Start : public GamePacket
{
public:
    s32 _currentPlayerId;
    s32 _totalPlayer;

protected:
    virtual Type OnType() const override { return Type::Start; }
};
}   // namespace _network::_packet