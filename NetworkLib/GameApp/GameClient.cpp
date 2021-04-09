#include "GameClient.h"
#include "GameServer.h"

void GameClient::HandleCmd(std::string recvMsg)
{
    std::stringstream sstr(recvMsg);

    std::string cmd;
    //sstr >> cmd;
    if(cmd == "POS") {
        _server->SendToAll("sssssssss");
    }
    //while(std::getline(sstr, cmd, '\n')) {
    //    //printf_s("%s\n",cmd.c_str());
    //    if(cmd == "POS") {
    //        _server->SendToAll("sssssssss");
    //    }
    //}
}
