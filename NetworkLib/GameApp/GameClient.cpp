#include "GameClient.h"
#include "GameServer.h"
#include "MyApp.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

void GameClient::HandleCmd(const std::string& recvMsg)
{
    std::stringstream sstrRecv(recvMsg);
    std::string       strRecv;

    std::vector<Player>& players = MyApp::Instance()->_players;

    json j = json::parse(recvMsg);
    std::cout << j << std::endl;
    std::string key = j["key"].get<std::string>();

    if(key == "Accept") {
        _clientState = ClientState::Connected;
    }
    else {
        throw ErrorHandler("Unknow Message");
    }

#if FALSE
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
#endif
}

void GameClient::SendPos()
{
    Player* player = MyApp::Instance()->_pPlayer;

    /*   json j;
    j["Player"][0]["id"]     = 1;
    j["Player"][0]["name"]   = "PlayerId";
    j["Player"][0]["action"] = "Move";

    j["Player"][1]["id"]     = 2;
    j["Player"][1]["name"]   = "PlayerId2";
    j["Player"][1]["action"] = "Moveing";

    SetSendBuffer(j.dump());*/
    SetSendBuffer(fmt::format("POS {} {} {}\n",
                              player->GetId(),
                              player->GetPos().x,
                              player->GetPos().y));
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
