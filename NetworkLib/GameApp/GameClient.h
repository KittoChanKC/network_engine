#pragma once
#include <string>
#include <sstream>
#include "Client/BaseClient.h"
#include "../Objects/Player.h"
#include "GamePacket.h"
using namespace _network::_packet;

class GameClient : public _network::BaseClient
{
public:
    void OnSend() override;   //! ‘—M
    void SendPacket(GamePacket& pkt);
    void OnRecv() override;   //! óM

    void OnRecvPacket(PacketType packetType, const std::vector<char>& buf);
    void OnRecvPacket(PacketType packetType, const std::string& buf);

    void HandleCmd(const std::string& recvMsg) override;

    void SendPos();

private:
};