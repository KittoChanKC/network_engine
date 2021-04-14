#include "GameClient.h"
#include "GameServer.h"
#include "MyApp.h"

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
