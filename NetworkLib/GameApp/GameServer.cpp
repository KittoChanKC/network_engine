#include "GameServer.h"
#include "GameClient.h"
#include "ServerConnection.h"

void GameServer::SendStartPkg()
{
    // Full String Sample
    // "Start {player_id} {total_player} {p1.pos.x} {p1.pos.y} {p2.pos.x} {p2.pos.y}\n"
    //_players.resize(_clients.size()+1);
    //_pPlayer = &_players[0];

    //for(int i = 0; i < _clients.size(); i++) {
    //    _clients[i]->SetSendBuffer(fmt::format("Start {} {} ", i+1, _players.size()));

    //    for(auto player : _players) {
    //        _clients[i]->SetSendBuffer(fmt::format("{} {} ", player.GetPos().x, player.GetPos().y));
    //    }
    //    _clients[i]->SetSendBuffer("\n");
    //    _clients[i]->PrintSendBuffer();
    //}
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
