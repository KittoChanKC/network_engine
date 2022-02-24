#include "ServerConnection.h"
#include "GameServer.h"
#include <sstream>
#include "MyApp.h"
#include "GamePacket.h"

namespace _network {
ServerConnection::ServerConnection()
{
}
ServerConnection::~ServerConnection()
{
}
void ServerConnection::OnConnected()
{
    BaseConnection::OnConnected();
}
void ServerConnection::HandleCmd(const std::string& recvMsg)
{
#if 0
    std::stringstream sstrFullRecv(recvMsg);
    std::string       strRecv;

    while(std::getline(sstrFullRecv, strRecv, '\n')) {
        std::stringstream sstrLineRecv(strRecv);
        std::string       cmd;
        sstrLineRecv >> cmd;

        if(cmd == "POS") {
            s32 id = 0;
            f32 x = 0.0f, y = 0.0f;
            sstrLineRecv >> id >> x >> y;
            // do someing...
            Player* player = &MyApp::Instance()->_players[id];
            player->SetPos(x, y);
            
            _server->SendToAllWithoutID(fmt::format("POS {} {} {}\n",
                                                    player->GetId(),
                                                    player->GetPos().x,
                                                    player->GetPos().y),
                                                    player->GetId());
        }
    }
#endif
    json recvJson = json::parse(recvMsg);
    std::cout << recvJson << std::endl;
    std::string key = recvJson["key"].get<std::string>();
    //_server;
 /*   if() {
    }*/
}
}   // namespace _network