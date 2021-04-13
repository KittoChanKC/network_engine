#pragma once
#include "Utility/Packet.h"

namespace _network::_packet {
enum class GamePacket
{
	None,
	Start
};

class Packet_Start : public Packet
{
public:
    s32 _currentPlayerId;
    s32 _totalPlayer;
};
}