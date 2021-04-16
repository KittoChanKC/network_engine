#include "GameServer.h"
#include "GameClient.h"
#include "ServerConnection.h"
#include "MyApp.h"

void GameServer::SendStartPkg()
{
    size_t connectionNum = _connections.size();

    std::vector<Player>& players = MyApp::Instance()->_players;

    players.resize(connectionNum);
    for(size_t i = 0; i < connectionNum; i++) {
        players[i].SetId((int)i);
    }

    // Full String Sample
    //"Start {player_id} {total_player} {p1.pos.x} {p1.pos.y} {p2.pos.x} {p2.pos.y}\n"
    for(int i = 0; i < connectionNum; i++) {
        _connections[i]->SetSendBuffer(fmt::format("Start {} {} ", i, connectionNum));

        for(auto p : players) {
            _connections[i]->SetSendBuffer(fmt::format("{} {} ",
                                                       p.GetPos().x,
                                                       p.GetPos().y));
        }
        _connections[i]->SetSendBuffer("\n");
    }
}
void GameServer::SetGameStart()
{
    _isStarted = true;
}
bool GameServer::IsStarted()
{
    return _isStarted;
}
//void GameServer::Draw(ImDrawList* drawList)
//{
//    for(auto player : _players) {
//        drawList->AddTriangleFilled(ImVec2(player.GetPos().x, player.GetPos().y - 12),
//                                    ImVec2(player.GetPos().x - 12, player.GetPos().y + 12),
//                                    ImVec2(player.GetPos().x + 12, player.GetPos().y + 12),
//                                    ImColor(255, 0, 0));
//    }
//}
uni_ptr<_network::BaseConnection> GameServer::CreateConnection()
{
    return std::make_unique<_network::ServerConnection>();
}
