#include "Utility/TypeContenter.h"

#include "GameClient.h"
#include "GameServer.h"
#include "MyApp.h"

void GameClient::OnSend()
{
}

void GameClient::SendPacket(GamePacket& pkt)
{
    std::vector<char> _tmp;
    auto type = pkt.GetType();
    pkt.Write(_tmp);

    _sendBuffer.insert(_sendBuffer.end(), _tmp.begin(), _tmp.end());
}

void GameClient::OnRecv()
{
    auto bytesInSocket = _socket.AvailableBytesToRead();
    if(!bytesInSocket) {
        Close();
        return;
    }

    const auto headerSize = sizeof(GamePacket::PacketSize) + sizeof(PacketType);

    // recv header
    if(_recvBuffer.size() < headerSize) {
        auto bytesToRead = headerSize - _recvBuffer.size();
        if(bytesInSocket < bytesToRead) {
            bytesToRead = bytesInSocket;
        }
        _socket.AppendRecv(_recvBuffer, bytesToRead);
        bytesInSocket -= bytesToRead;
    }

    // not enough for header
    if(_recvBuffer.size() < headerSize)
        return;

    // recv body
    Deserializer           deser(_recvBuffer);
    GamePacket::PacketSize packetSize;
    PacketType             packetType;
    deser.io_fixed(packetSize);
    deser.io_fixed(_network::my_enum_to_int(packetType));

    if(packetSize < headerSize)
        throw ErrorHandler("invalid header");

    auto bytesToRead = packetSize - headerSize;
    if(bytesInSocket < bytesToRead) {
        bytesToRead = bytesInSocket;
    }

    _socket.AppendRecv(_recvBuffer, bytesToRead);

    // not enough for body
    if(_recvBuffer.size() < packetSize)
        return;

    assert(_recvBuffer.size() == packetSize);

    printf("onRecvPacket %d\n", _network::my_enum_to_int(packetType));
    OnRecvPacket(packetType, _recvBuffer.data());
    _recvBuffer.clear();
}

void GameClient::OnRecvPacket(PacketType packetType, const std::vector<char>& buf)
{
    switch(packetType) {
        case PacketType::Start:
        {
            GamePacket_Start pkt;
            pkt.Read(buf);
            printf("chat: \"%d\"\n", pkt._currentPlayerId);
        } break;
    }
}

void GameClient::OnRecvPacket(PacketType packetType, const std::string& buf)
{
    switch(packetType) {
        case PacketType::Start:
        {
            GamePacket_Start pkt;
            pkt.Read(buf);
            printf("chat: \"%d\"\n", pkt._currentPlayerId);
        } break;
    }
}

void GameClient::HandleCmd(const std::string& recvMsg)
{
    std::stringstream sstrRecv(recvMsg);
    std::string       strRecv;

    std::vector<Player>& players = MyApp::Instance()->_players;

    while(std::getline(sstrRecv, strRecv, '\n')) {
        std::stringstream sstr(strRecv);
        std::string       cmd;
        sstr >> cmd;
        if(cmd == "Start") {
            int myId, totalPlayer;
            sstr >> myId >> totalPlayer;
            players.clear();
            players.resize(totalPlayer);

            for(int i = 0; i < totalPlayer; i++) {
                players[i].SetId(i);
                if(i == myId) {
                    MyApp::Instance()->_pPlayer = &players[i];
                }
            }

            MyApp::Instance()->_isStarted = true;
        }
        else if(cmd == "POS") {
            s32 id;
            f32 x, y;
            sstr >> id >> x >> y;

            players[id].SetPos(x, y);
        }
    }
}

void GameClient::SendPos()
{
    Player* player = MyApp::Instance()->_pPlayer;
    /*SetSendBuffer(fmt::format("POS {} {} {}\n",
                              player->GetId(),
                              player->GetPos().x,
                              player->GetPos().y));*/
    GamePacket_POS packet;
    packet._currentPlayerId = player->GetId();
    packet._x               = player->GetPos().x;
    packet._y               = player->GetPos().y;

    SendPacket(packet);
    //printf_s("%s", fmt::format("POS {} {} {}\n", _pPlayer->GetId(), _pPlayer->GetPos().x, _pPlayer->GetPos().y).c_str());
}

//void GameClient::Draw(ImDrawList* drawList)
//{
//    for(auto player : _players) {
//        drawList->AddTriangleFilled(ImVec2(player.GetPos().x, player.GetPos().y - 12),
//                                    ImVec2(player.GetPos().x - 12, player.GetPos().y + 12),
//                                    ImVec2(player.GetPos().x + 12, player.GetPos().y + 12),
//                                    ImColor(255, 0, 0));
//    }
//}
