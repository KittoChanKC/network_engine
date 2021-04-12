#include "GameClient.h"
#include "GameServer.h"

void GameClient::HandleCmd(const std::string& recvMsg)
{
    std::stringstream sstrRecv(recvMsg);
    std::string       strRecv;

    while(std::getline(sstrRecv, strRecv, '\n')) {
        std::stringstream sstr(strRecv);
        std::string       cmd;
        sstr >> cmd;
        if(cmd == "Start") {
            int totalPlayer, myId;
            sstr >> myId >> totalPlayer;
            _players.clear();
            _players.resize(totalPlayer);

            for(int i = 0; i < totalPlayer; i++) {
                _players[i].SetId(i);
                if(i == myId) {
                    _pPlayer = &_players[i];
                }
            }

            _gameStart = true;
        }
        if(cmd == "POS") {
            if(_players.size() > 0) {
                s32 id;
                f32 x, y;
                sstr >> id >> x >> y;

                _players[id].SetPos(x, y);
                //_server->SendToAll(fmt::format("POS {} {} {}\n", id, _players[id].GetPos().x, _players[id].GetPos().y));
            }
            else {
                s32 id;
                sstr >> id;
                _server->SendToAllWithoutID(recvMsg, id);
            }
        }
    }
}

void GameClient::SendPos()
{
    //_server->SendToAll(fmt::format("POS {} {} {}\n", _pPlayer->GetId(), _pPlayer->GetPos().x, _pPlayer->GetPos().y));
    SetSendBuffer(fmt::format("POS {} {} {}\n", _pPlayer->GetId(), _pPlayer->GetPos().x, _pPlayer->GetPos().y));
    //printf_s("%s", fmt::format("POS {} {} {}\n", _pPlayer->GetId(), _pPlayer->GetPos().x, _pPlayer->GetPos().y).c_str());
}

void GameClient::Draw(ImDrawList* drawList)
{
    for(auto player : _players) {
        drawList->AddTriangleFilled(ImVec2(player.GetPos().x, player.GetPos().y - 12),
                                    ImVec2(player.GetPos().x - 12, player.GetPos().y + 12),
                                    ImVec2(player.GetPos().x + 12, player.GetPos().y + 12),
                                    ImColor(255, 0, 0));
    }
}
