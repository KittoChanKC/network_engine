#pragma once
#include <string>
#include <sstream>
#include "Client/BaseClient.h"
#include "GameServer.h"

class GameClient : public _network::BaseClient 
{
public: 
    void HandleCmd(std::string recvMsg) override
    {
        std::stringstream sstr(recvMsg);

        std::string cmd;
        //sstr >> cmd;

        if(cmd == "POS") {
            _server->SendToAll("sssssssss");
        }
    }
};
